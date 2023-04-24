/**
 * @file i_data_source.h
 * @brief В этом файле описан интерфейс для взаимодействия с базами данных
 * @author Михаил Овакимян (DaMagus26)
 */

#pragma once
#include <chrono>
#include <string>
#include <vector>

using time_point = std::chrono::system_clock::time_point;

class IDataSource {
  virtual std::vector<int> selectEntriesOverInterval(const time_point &start, const time_point &end) const = 0;
  virtual int selectLastEntry(int room_id) const = 0;
  virtual std::vector<int> selectAllRooms() const = 0;
  virtual void insertEntry(int measurement, time_point time, int room_id) = 0;
};

class Server {
 public:
  Server(const std::vector<std::string> &x,
         const std::string par_name,
         const std::string excessively_alt_name,
         const std::vector<std::string> &,
         const std::string par_surname) : name(par_name),
                                          surname(par_surname),
                                          completely_unneccessarily_long_alt_name(excessively_alt_name) {}
 private:
  std::string name;
  std::string surname;
  std::string completely_unneccessarily_long_alt_name;
};