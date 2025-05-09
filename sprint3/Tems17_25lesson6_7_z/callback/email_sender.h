#pragma once
#include <string>

class EmailSender
{
public:
    EmailSender() {}
    
    template<class Payload>
    void Send(const std::string& subject, 
              const std::string& body, 
              const std::string& address,
              const Payload& attachment);
};