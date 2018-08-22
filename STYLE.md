# Introduction

Coding style has a tendency to be highly personal. A little bit of inconsistency can be tolerated and probably won't stop your pull request from being merged. The only thing that will be almost *required* is the usage of tabs for indentation, since that needs to be consistent and tabs are best because they can be configured to be however long the user chooses. Because they can and will be different widths among different developers, spaces should be always used for alignment instead of tabs. Tabs should not appear on a line after any non-tab character without good reason.

Everything else in this document is a guideline and probably won't stop your pull request from being merged. This policy is subject to change in the future.

# Guidelines

## Naming

When it comes to naming identifiers, `snake_case` is the preferred style. Type names should end with `_t`. In general, descriptive names are preferred to very short names. For short-scoped variables, short names are okay, as well as when the variable's purpose can be immediately identified by its short name (`i` and `j` for iterators, `x`,`y`, and `z` for coordinates, `w`, `h`, and `l` for dimensions, or any other such commonly recognized names).

## Indentation

As stated earlier, tabs are the preferred form of indentation.

### switch-case

The `case` should be in the same column as the `switch`. Fall-through is acceptable, but should probably include a comment if it's not obvious.

```c
switch(value) {
case 0x7777:
case 0x8888:
case 0x9999:
	break;
case 0xAAAA:
	do_something();
	// fall-througth
case 0xBBBB:
	do_another_thing();
	break;
}
```

## Braces, Spaces, and Parentheses

There should be no whitespace between a function call and its parentheses (or something that looks like a function call; e.g. macros, keywords like if or sizeof and such), and none between the parentheses and their contents. Commas should be followed by spaces. Curly brackets should go on the same line with a space before them.

```c
void foo(int bar, int baz) {
	return sizeof(bar);
}
```

Whether or not there are newlines around the contents of the brackets depends on what's the most readable. If there is a long string of similar `if` statements, the best option would be to reorganize your code so that you don't have such a long string of similar `if` statements, but failing that, putting each on one line is acceptable and encouraged. Alignment of brackets and such is up to the author. Remember, tabs are not to be used for alignment.

```c
if(condition)        { do_something(); }
if(longer condition) { do_thing(); }
if(third condition)  { return; }
```

If statements should *always* have brackets. Not only is it less [prone to](https://i.imgur.com/UQWytqj.png) [error](https://nvd.nist.gov/vuln/detail/CVE-2014-1266), but it means that if someone needs to add another statement, they won't have to go in and add the brackets around it. `else` and `else if` keywords should be placed on the same line as both the closing brace `}` and the following opening brace `{`.

```c
if(a) {
	single_statement();
} else if(b) {
	another_single_statement();
} else {
	two();
	statements();
}
```

Whitespace should be applied around binary and ternary operators whenever it improves readability (this is most cases), but not around unary operators or the `->` and `.` structure member operators. Parentheses should be used to improve readability when multiple operators are used. If I have to find an order of operations table to understand your code, *please* use parentheses.

```c
return a ? (b ? (c + d) * e-- : -f.g) : h->i;
```

Compound assignment operators should be adjacent to the variable being assigned.

```c
a+= b;
```

The `*` symbol when used for pointers and derefencing should be adjacent to the identifier. If there is no identifier (such as when casting), putting it next to the type is okay. Casts should have a space after them.

```c
uint32_t example(uint64_t *a) {
	return *((uint32_t*) a);
}
```

## Typedefs

Typedeffing structures is acceptable and encouraged (as long as the name ends with `_t)`.

## Error Handling and Goto

Goto statements should be used for error handling, just like in the Linux kernel. It reduces code duplication and moves error-handling code out of the way, making the intended behaviour of the function more available for reading. This is particularly useful when dealing with many functions that return `result_t`. When it comes to naming labels, the current convention is to name them after the most recent resource to be acquired that needs to be freed.

```c
void func() {
	result_t r = RESULT_OK; // this is one of those cases where the meaning of the variable is clear both from usage and because it's a recurring pattern
	if((r =  sm_init()) != RESULT_OK) { goto fail; }
	if((r = bsd_init()) != RESULT_OK) { goto fail_sm; }
	
	// code goes here
	
	bsd_finalize();
fail_sm:
	sm_finalize();
fail:
	return r;
}
```

## Header Files

We use the newer `#pragma once` instead of conventional `#ifndef HEADER_H` header guards. Header files go in `include/libtransistor/`, and the directory tree should generally match `lib/`. Implementations of functions declared in header files should generally go in a `.c` file of the same name in the same place in the directory tree. Additionally, header files and c files should include only those header files which they need to include. The `libtransistor/nx.h` header is intended as a convenience for programs using the library and should not be used within the library itself. Each c file should include the most relevant header file before any others, to ensure that it it not missing any dependencies.
