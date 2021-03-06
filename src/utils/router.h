#ifndef __MTX_ROUTER_H__
#define __MTX_ROUTER_H__
#include <string>
#include <map>
#include <functional>

namespace MTX {

struct Router{

    Router(const std::string& base_path="/v1/accounts");

    ~Router();

    typedef std::function<std::string
                (const std::string& path,
                 const std::map<std::string, std::string>& qs,
                 const std::map<std::string, std::string>& headers,
                 const std::string& account_name,
                 const std::string& body)> request_async_action;

    /*
    Add a route and bind
    @param method : is the request method : PUT, POST, etc
    @param action : is the last sub at the path, ie for :
    /v1/accounts/<account>/shadow then the action is shadow
    */
    void addAsyncRoute(const std::string& method,
                       const std::string& action,
                       request_async_action f);

    /*
    Routes a request based on the path and method. If the
    route was not found then return false, true otherwise
    */
    bool route(const std::string& method,
               const std::string& path,
               const std::map<std::string, std::string>& qs,
               const std::map<std::string, std::string>& headers,
               const std::string& body,
               std::string& response_body);

private:

    bool check_base_path(const std::string& path);

    std::map<std::string, request_async_action> get_actions;
    std::map<std::string, request_async_action> post_actions;
    std::map<std::string, request_async_action> put_actions;

    std::string base_path;
    
};


}

#endif
