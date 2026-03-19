#pragma once
#include <Geode/utils/web.hpp>
#include <Geode/utils/async.hpp>
#include <matjson.hpp>

using namespace geode::prelude;

class GDAuthAPI {
public:
    static inline std::string getBaseURL() {
        return "http://api--gdplatform.netlify.app";
    }

    static void generateVerificationCode(int accountID, std::function<void(std::string)> callback) {
        matjson::Value body;
        body["accountId"] = accountID;

        auto req = web::WebRequest();
        req.bodyJSON(body);

        geode::async::spawn(req.post(getBaseURL() + "/geodesdk/gd-oauth/generate-code"), [callback](auto const& res) {
            if (res.ok()) {
                auto json = res.json().unwrapOr(matjson::Value());
                if (json.contains("code") && json["code"].isString()) {
                    callback(json["code"].asString().unwrapOr("ERR!"));
                    return;
                }
            }
            callback("ERR!");
        });
    }

    static void checkAuthStatus(const std::string& code, std::function<void(std::string)> callback) {
        auto req = web::WebRequest();
        
        geode::async::spawn(req.get(getBaseURL() + "/geodesdk/gd-oauth/status?code=" + code), [callback](auto const& res) {
            if (res.ok()) {
                auto json = res.json().unwrapOr(matjson::Value());
                callback(json["status"].asString().unwrapOr("pending"));
            } else {
                callback("pending");
            }
        });
    }
};