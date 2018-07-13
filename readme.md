# Nano-pass-lisp

Nano-pass-lisp is a micro lisp interpreter developed in C++ and it has been conceived as toy project to learn about interpreter of programming language.
~~It doesn't have a proper a Parser and Error Handling yet but they will come.~~

Nano-lisp is based on a REPL which will support loading of source code in a modular way through a special form (include file) (? is there anything already).

The special form planned are 

- ( **if** `condition` `true_expression` `else_expression`) conditional operator
- (let ) todo
- ( **defvar** `name` `value` ) 
- ( **defun** `name` `expression` )
- ( **include** `filename`)  
- **math operators/functions** - (+ - / * %)
- **string operators/functions** - (substring, startswith, endswith, replace, contains, compare, at)

The primitive types are

- boolean
- int64
- string
