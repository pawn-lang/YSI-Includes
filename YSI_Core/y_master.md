# y_master

Provides `foreign` and `global` (used like `forward` and `public` respectively) to allow you to define functions that may be in another script and call them directly.  This makes remote calls that normally use `CallRemoteFunction` safer as you get compile-time parameter checks and no specifier string.  It also means the functions don't have to be in another script and will instead by called directly.  This leads to the most important use of y_master - protecting your code from rogue developers.  You can restrict it so only the server has all the code, while your coders only have parts of the code in source, and parts pre-compiled.

## YSI

For general YSI information, see the following links:

* [Installation](../installation.md)
* [Troubleshooting](../troubleshooting.md)

## Documentation

* [Quick Start](y_master/quick-start.md) - One very simple example of getting started with this library.
* [Features](y_master/features.md) - More features and examples.
* [FAQs](y_master/faqs.md) - Frequently Asked Questions, including errors and solutions.
* [API](y_master/api.md) - Full list of all functions and their meaning.
* [Internal](y_master/internal.md) - Internal developer documentation for the system.

## External Links

These are links to external documentation and tutorials; both first- and third-party.  Note that these may be incomplete, obsolete, or otherwise inaccurate.

