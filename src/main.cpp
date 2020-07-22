#include <aws/lambda-runtime/runtime.h>
#include <json/json.h>

using namespace aws::lambda_runtime;

invocation_response my_handler(invocation_request const& request)
{

   Json::Value root(Json::objectValue);
   root["hi"] = Json::Value("there");

   return invocation_response::success(root.toStyledString(), "application/json");
}

int main()
{
   run_handler(my_handler);
   return 0;
}