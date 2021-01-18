# regular-expressions
This program matches regular expression to strings

In this program I represent regualr expressions as binary trees. There are 3 types of nodes,CHR, SEQ, ALT. CHR matches to a character, SEQ is a sequential composition which has two children as regular expressions which both must match. ALT has two children as regular expressions where either the first matches or the second child matches.

Regexp              "ab" "xab" "xba" "axu"

x(ab+ba)            ✗     ✓     ✓     ✗

(a+b+c)(x+y)(u+v+w) ✗     ✗     ✗     ✓


Here, x, a, b, c, u, and v are characters, (+) denotes alternative and characters side by side denotes sequential composition.
