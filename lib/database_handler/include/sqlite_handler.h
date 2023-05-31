/**
 * @file sqlite_handler.h
 * @brief В этом файле описан класс для взаимодействия с SQLite
 * @author Михаил Овакимян (DaMagus26)
 */

#ifndef QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_SQLITE_HANDLER_H_
#define QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_SQLITE_HANDLER_H_

#include <sqlite3.h>
#include <nlohmann/json.hpp>

#include <chrono>
#include <string>
#include <vector>

#include "i_data_source.h"

using time_point = std::chrono::system_clock::time_point;

class SQLiteHandler final : public IDataSource {
 public:
  SQLiteHandler() = default;
  explicit SQLiteHandler(const std::string& db_path);
  ~SQLiteHandler();
  std::vector<int> selectEntriesOverInterval(
      const time_point& start, const time_point& end) const override;
  std::string selectEntriesOverIntervalString(
      const time_point& start, const time_point& end) const override;
  nlohmann::json selectEntriesOverIntervalJSON(
      const time_point &start, const time_point &end) const override;
  nlohmann::json selectLastEntryJSON(
      int room_id
  ) const override;
  int selectLastEntry(int room_id) const override;
  std::vector<int> selectAllRooms() const override;
  void insertEntry(int measurement, time_point time, int room_id) override;
  void deleteOlderEntries(int max_age_months = 6);

  // Deletions
  SQLiteHandler(const SQLiteHandler&) = delete;
  SQLiteHandler& operator=(const SQLiteHandler&) = delete;

 private:
  static std::string toISO8061(const time_point& time);
  sqlite3* db_{};
};

#endif  // QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_SQLITE_HANDLER_H_