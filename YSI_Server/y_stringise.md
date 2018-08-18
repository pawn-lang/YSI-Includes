# y_stringise

Similar to `#`, but more complete in that it handles brackets, commas, and more.  Note that the brackets it handles must be matched.  It is also different to `#` in other ways - quotes are converted to `` ` ``, concatenation is not allowed, and te output is enclosed in `"`s:

| Input                | Output      |
| -------------------- | ----------- |
| `#A "B"`             | `"AB"`      |
| `STRINGISE__(A)"B"`  | `<invalid>` |
| `STRINGISE__(A "B")` | ``"A`B`"``  |

## YSI

For general YSI information, see the following links:

* [Installation](../installation.md)
* [Troubleshooting](../troubleshooting.md)

## Documentation

* [Quick Start](y_flooding/quick-start.md) - One very simple example of getting started with this library.
* [Features](y_flooding/features.md) - More features and examples.
* [FAQs](y_flooding/faqs.md) - Frequently Asked Questions, including errors and solutions.
* [API](y_flooding/api.md) - Full list of all functions and their meaning.
* [Internal](y_flooding/internal.md) - Internal developer documentation for the system.

## External Links

These are links to external documentation and tutorials; both first- and third-party.  Note that these may be incomplete, obsolete, or otherwise inaccurate.

