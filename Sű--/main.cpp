#include <iostream>
#include <string>
#include <curl/curl.h>


static size_t __cdecl WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	auto* res = static_cast<std::string*>(userp);
	res->append(static_cast<char*>(contents), size * nmemb);
	return size * nmemb;
}

CURLcode GET(CURL* curl, const char* url, std::string* buffer)
{
	curl_easy_reset(curl);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);

	auto res = curl_easy_perform(curl);
	return res;
}

CURLcode POST(CURL* curl, const char* url, const std::string& msg)
{
	curl_easy_reset(curl);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, FALSE);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, msg.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, msg.size());

	return curl_easy_perform(curl);
}

int main(int argc, char** argv)
{
	CURL* curl = curl_easy_init();
	CURLcode res;
	std::string readBuffer;

	if (!curl)
	{
		std::cerr << "Error with initialization\n";
		return 1;
	}

	std::string toPost = "Hi from desktop";
	GET(curl, "https://www.google.com", &readBuffer);

	//ntfy.sh/saso-notifications

	//std::cout << readBuffer << std::endl;

	auto currRes = POST(curl, "ntfy.sh/saso-notifications", toPost);

	std::cerr << curl_easy_strerror(currRes) << "\n";
	
	curl_easy_cleanup(curl);
	return 0;
}