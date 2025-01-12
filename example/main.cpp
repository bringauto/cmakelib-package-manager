
#include <nlohmann/json.hpp>
#include <curl/curl.h>

#include <iostream>



size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

int main(int argc, char **argv) {
    nlohmann::json j;

    j["TestJson"] = "ok";
    std::cout << j.dump() << std::endl;

    auto curl = curl_easy_init();
    if (!curl) {
        return 1;
    }
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/repos/bringauto/package-tracker/contributors?anon=true&key=value");
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_USERPWD, "user:pass");
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.79.1");
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
    
    std::string response_string;
    std::string header_string;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
 
    curl_easy_perform(curl);
    
    char* url;
    long response_code;
    double elapsed;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
    curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

    std::cout << "response_code: " << response_code << std::endl;
    std::cout << "elapsed:       " << elapsed << std::endl;
    std::cout << "effective url: " << url << std::endl;

    curl_easy_cleanup(curl);
    curl = NULL;
    
    return 0;
}