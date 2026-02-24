#pragma once
#include <Geode/utils/web.hpp>
#include <matjson.hpp>

using namespace geode::prelude;

class GDAuthAPI
{
public:
    static inline std::string getBaseURL() {
        return "http://api--gdplatform.netlify.app"; 
    }

    static void generateVerificationCode(int accountID, std::function<void(std::string)> callback)
    {
        matjson::Value body;
        body["accountId"] = accountID;

        std::string jsonStr = body.dump();
        
        // --- CORRECCIÓN AQUÍ ---
        // Convertimos el string a ByteVector (std::vector<uint8_t>)
        geode::ByteVector payload(jsonStr.begin(), jsonStr.end());

        web::WebRequest()
            .header("Content-Type", "application/json")
            .body(payload) // Ahora el tipo coincide perfectamente
            .post(getBaseURL() + "/geodesdk/gd-oauth/generate-code")
            .listen([callback](web::WebResponse *res)
            {
                if (res->ok()) {
                    auto json = res->json().unwrapOr(matjson::Value());
                    if (json.contains("code")) {
                        callback(json["code"].asString().unwrapOr("ERR!"));
                    } else {
                        callback("ERR!");
                    }
                } else {
                    callback("Error de Red");
                } 
            });
    }

    static void checkAuthStatus(std::string const& code, std::function<void(std::string)> callback)
    {
        web::WebRequest()
            .get(getBaseURL() + "/geodesdk/gd-oauth/status?code=" + code)
            .listen([callback](web::WebResponse *res)
            {
                if (res->ok()) {
                    auto json = res->json().unwrapOr(matjson::Value());
                    callback(json["status"].asString().unwrapOr("pending"));
                } else {
                    callback("pending");
                }
            });
    }
};