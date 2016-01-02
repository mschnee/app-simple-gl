# OS-Specific Implementations
This library contains interface classes and OS-specific implementations.
Thankfully, there isn't much that's OS-specific; so far:
* pathnames
* shell/process launching with admin privileges

When you find you need to ```#if defined(WIN32)``` to do a platform-specific thing, bring it here,
make an appropriate interface, and implement as necessary.