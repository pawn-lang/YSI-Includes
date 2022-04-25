# Features




## Accepted argument forms

### Collated short-form.

```
-akgd
```

Is equivalent to:

```
-a -k -g -d
```

### Implicit `true`/`false`.

```
-y
```

Is equivalent to:

```
-y=true
```

Or:

```
-y=1
```

### pawncc style `-`/`+`.

```
-x+
```

Is equivalent to:

```
-x=true
```

```
-x-
```

Is equivalent to:

```
-x=false
```

(Useful when the default is `true`, but can be ommitted entirely when the default is `false`).

### pawncc style `:`.

As well as `=`, short-form arguments can be separated from their parameter with `:`:

```
-z:7
```

### windows style '/'.

As well as `-`, arguments can be started with `/`.  However, this has very different semantics to `-`.  Because there is no `--` equivalent the argument name is never collated, so this:

```
/k
```

Is equivalent to:

```
-k
```

However, this:

```
/klm
```

Is equivalent to:

```
--klm
```

And *not*:

```
-k -l -m
```

### Long- and short-form pairs.

```
-h
```

Can be configured to be the same as:

```
--help
```

### Long-form separated arguments.

Long-form arguments can be separated from their parameters by a space:

```
--players 7
```

### Double-quotes enclosing long parameters

```
--motd "Hello and welcome to my server!"
```

### Only use the last argument.

```
-c=7 -c=6 -c=9
```

Will just return `-c` = `9`.

Unless...

### Array parameters.

If configured as an array, this:

```
-c=7 -c=6 -c=9
```

Will return `-c` = `{7, 6, 9}`.

### Comma-separation of arrays.

If configured as an array, this:

```
-c=7,6,9
```

Will, as above, return `-c` = `{7, 6, 9}`.

### Rest

A `--` parameter with no name separates the initial parameters from the *rest* parameters.  The *rest* parameters are always returned as a single large string:

```
--foo --bar -- Hello world!
```

Will have "Hello world!" as a single parameter.  Absolutely everything after the lone `--` is this parameter, it can't be ended again.

### Parameters starting with `-`.

If you want a parameter to start with `-` (or `/`), which are usually used to denote a new argument, they MUST be separated by `=` or `:`, not a space:

```
-e=--i
```

For almost exclusively this corner-case (it is not usually recommended) the entire argument and parameter may be enclosed in double quotes:

```
"--decrement --i"
```

