#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <aws/dynamodb/model/ScanRequest.h>
#include <aws/lambda-runtime/runtime.h>
#include <iostream>

using namespace aws::lambda_runtime;

invocation_response my_handler()
{

   Aws::Client::ClientConfiguration clientConfig;
   // clientConfig.region = std::getenv("AWS_REGION");
   clientConfig.region = "eu-west-1";
   Aws::DynamoDB::DynamoDBClient client(clientConfig);

   const Aws::DynamoDB::Model::ScanRequest scanRequest = Aws::DynamoDB::Model::ScanRequest().WithTableName("dev.service-catalogue.services");
   std::cout << "about to scan" << std::endl;
   const Aws::DynamoDB::Model::ScanOutcome &scanResult = client.Scan(scanRequest); // Time out here
   std::cout << "scan complete" << std::endl;

   if (scanResult.IsSuccess()){
       for (const Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue> &item : scanResult.GetResult().GetItems()){
          for (const auto &i : item) {
             std::cout << i.first.c_str() << std::endl;
          }
       }
   }else {
      std::cout << "error: " << scanResult.GetError().GetMessage() << std::endl;
   }

   return invocation_response::success(scanResult.IsSuccess() ? "true" : "false", "application/json");
}

int main()
{
   Aws::SDKOptions options;
   options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Trace;
   Aws::InitAPI(options);

   // run_handler(my_handler);
   my_handler();


   Aws::ShutdownAPI(options);
   return 0;
}