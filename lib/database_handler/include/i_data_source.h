/**
 * @file i_data_source.h
 * @brief В этом файле описан интерфейс для взаимодействия с базами данных
 * @author Михаил Овакимян (DaMagus26)
 */

#ifndef QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_I_DATA_SOURCE_H_
#define QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_I_DATA_SOURCE_H_

#include <chrono>
#include <string>
#include <vector>

using time_point = std::chrono::system_clock::time_point;

class IDataSource {
public:
  virtual std::vector<int> selectEntriesOverInterval(const time_point &start, const time_point &end) const = 0;
  virtual int selectLastEntry(int room_id) const = 0;
  virtual std::vector<int> selectAllRooms() const = 0;
  virtual void insertEntry(int measurement, time_point time, int room_id) = 0;
};

#endif //QUEUE_ANALYSER_LIB_DATABASE_HANDLER_INCLUDE_I_DATA_SOURCE_H_