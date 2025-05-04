# Asynchronous Pool
This library provides you with a container that is unordered and thread-safe.

This particular implementation is totally unfair to the underlying objects. Meaning that if you acquire objects sequentially, you will always get the same object. And only if it is locked do you get a different one.

This is probably better for caching, but we will see.
