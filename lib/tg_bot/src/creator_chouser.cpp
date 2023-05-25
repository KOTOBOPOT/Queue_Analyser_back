#include "creator_chouser.h"

namespace QueueBot {
IBotHandler::Ptr CreatorChouser::create(nlohmann::json value) {
  return creators_.at(value.at("class_tag"))->create(value);
}

void CreatorChouser::operator+=(
    std::pair<std::string, IHandlerCreator::Ptr>&& value) {
  creators_[value.first] = value.second;
}
}  // namespace QueueBot