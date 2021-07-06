## Aws cpp sdk dynamo timeout

When building a lambda with the aws sdk, the lambda works correctly however when performing an action on dynamo the code just locks up and lambda times out.

## Recreate

```
vagrant up
vagrant ssh
cd /usr/src/hello
mkdir build
cd build
cmake ..
make && make aws-lambda-package-hello
```

Uploading this to aws and running the lambda times out.