/**
 * @file sqlite_handler.cpp
 * @brief В этом файле написана реализация класса для взаимодействия с SQLite
 * @author Михаил Овакимян (DaMagus26)
 */

#include "../include/sqlite_handler.h"
#include "../include/database_exceptions/db_access_exc.h"
#include "../include/database_exceptions/query_execution_exc.h"
#include "../include/database_exceptions/query_preparation_exc.h"
#include <sqlite3.h>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

/**
 * @throws DBAccessException Вызывается, если не удается открыть указанынй файл
 * @param db_path Строка, содержащая путь к существующему файлу .db (Если файла не существует, будет создан новый, однако настраивать БД придется отдельно)
 */
SQLiteHandler::SQLiteHandler(const std::string& db_path) : db_(nullptr) {
  int rc = sqlite3_open(db_path.c_str(), &db_);
  if (rc) {
    sqlite3_close(db_);
    throw DBAccessException("Cannot connect to database: " + std::string(sqlite3_errmsg(db_)));
  }
}

SQLiteHandler::~SQLiteHandler() {
  sqlite3_close(db_);
}

/**
 * @brief Преобразует объект std::chrono::system_clock::time_point в строку по стандарту ISO8061
 * @param time Объект std::chrono::system_clock::time_point
 * @return Строка, содержащая время в формате "YY-MM-DD HH:MM:SS.sss"
 */
std::string SQLiteHandler::toISO8061(const time_point& time) {
  auto time_since_epoch = time.time_since_epoch();
  auto seconds_since_epoch = std::chrono::duration_cast<std::chrono::seconds>(time_since_epoch);
  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time_since_epoch) - seconds_since_epoch;

  std::time_t tt = std::chrono::system_clock::to_time_t(time);
  std::tm tm = *std::localtime(&tt);
  char buffer[100];

  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
  std::string result = buffer;
  result += "." + std::to_string(milliseconds.count()).substr(0, 3);

  return result;
}

/**
 * @brief Запросов всех замеров за указанный интервал
 * @param start Объект std::chrono::system_clock::time_point, начало интервала
 * @param end Объект std::chrono::system_clock::time_point, конец интервала
 * @return std::vector<int> Массив замеров отсортированный по времени снятия по возрастанию
 * @throws QueryPreparationException Вызывается, если не удается обработать SQL запрос
 */
std::vector<int> SQLiteHandler::selectEntriesOverInterval(const time_point &start, const time_point &end) const {
  std::vector<int> results{};
  sqlite3_stmt *stmt;
  std::string query = "SELECT size FROM QueueSnapshots WHERE timestamp BETWEEN ? AND ? ORDER BY timestamp ASC;";

  int rc = sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    throw QueryPreparationException("Failed to prepare the statement: " + std::string(sqlite3_errmsg(db_)));
  }

  sqlite3_bind_text(stmt, 1, toISO8061(start).c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, toISO8061(end).c_str(), -1, SQLITE_TRANSIENT);

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    results.push_back(sqlite3_column_int(stmt, 0));
  }
  sqlite3_finalize(stmt);

  return results;
}

/**
 * @brief Возвращает последний замер с камеры в указанной столовой
 * @param room_id Уникальный идентификатор столовой
 * @return int Размер очереди
 * @throws QueryPreparationException Вызывается, если не удается обработать SQL запрос
 */
int SQLiteHandler::selectLastEntry(int room_id) const {
  int result = -1;
  sqlite3_stmt *stmt;
  std::string query = "SELECT size FROM QueueSnapshots WHERE canteen_id = ? ORDER BY timestamp DESC LIMIT 1;";

  int rc = sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    throw QueryPreparationException("Failed to prepare the statement: " + std::string(sqlite3_errmsg(db_)));
  }

  sqlite3_bind_int(stmt, 1, room_id);

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    result = sqlite3_column_int(stmt, 0);
  }

  sqlite3_finalize(stmt);
  return result;
}

/**
 * @brief Возвращает массив всех столовых, записанных в БД
 * @return std::vector<int> Массив canteen_id
 * @throws QueryPreparationException Вызывается, если не удается обработать SQL запрос
 */
std::vector<int> SQLiteHandler::selectAllRooms() const {
  std::vector<int> results{};
  sqlite3_stmt *stmt;
  std::string query = "SELECT DISTINCT canteen_id FROM QueueSnapshots ORDER BY canteen_id;";

  int rc = sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    throw QueryPreparationException("Failed to prepare the statement: " + std::string(sqlite3_errmsg(db_)));
  }

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    results.push_back(sqlite3_column_int(stmt, 0));
  }
  sqlite3_finalize(stmt);

  return results;
}

/**
 * @brief Вставляет новое значение в БД
 * @param measurement Размер очереди в момент записи
 * @param time Время записи
 * @param room_id Идентификатор столовой
 * @throws QueryExecutionException Вызывается, если не удается выполнить SQL запрос
 */
void SQLiteHandler::insertEntry(int measurement, time_point time, int room_id) {
  sqlite3_stmt *stmt;
  std::string query = "INSERT INTO QueueSnapshots (timestamp, size, canteen_id) VALUES (?, ?, ?)";

  int rc = sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    throw QueryPreparationException("Failed to prepare the statement: " + std::string(sqlite3_errmsg(db_)));
  }

  sqlite3_bind_text(stmt, 1, toISO8061(time).c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 2, measurement);
  sqlite3_bind_int(stmt, 3, room_id);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    throw QueryExecutionException("Failed to prepare the statement: " + std::string(sqlite3_errmsg(db_)));
  }

  sqlite3_finalize(stmt);
}
