// Copyright...
//  license...
//  Author: HMS
//  Introduction: This is a prototypical programming--------------------------------------------------Google C++ Style Guide
#ifndef PROJECT_EVENTLOOP_H_
#define PROJECT_EVENTLLOP_H_

#include <vector>
#include <string>

using std::string;

class Channel;

namespace mynamespace
{
   class eventLoop : public CallbackInterface
   {
   public:
      typedef std::vector<int> intVector;
      enum urlTableErrors
      {
         ERROR_OT_OF_MEMORY = 0,
         ERROR_MALFORMED_INPUT,
      };
      explicit eventLoop(const int &xx);

      void Add(const string &input, Channel *output) {}
      int num_entries() const { return num_entries_; }
      void set_num_entries(int num_entries) { num_entries_ = num_entries; }

   private:
      DISALLOW_COPY_AND_ASSIGN(eventLoop);
      const int kDaysInWeek = 7;
      int num_entries_;
      int num_complcated_connections_;

      Channel *channel_;
   };
} // namespace mynamespace

#endif // PROJECT_EVENTLOOP_H_