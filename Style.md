# DS Style Guide

## Terminology
### Case Type
1. `cammelCase`
Words are combined with first letter in each word capitalized except the first word. 
For an example: `lifeIsGood`, `iMustBeJoking`, `invertedBinaryTree`

2. `snake_case`
Words are combined with underscore sandwiched between words. 
For an example: `life_is_bad`, `i_am_speaking_the_truth`, `inverted_binary_tree`

3. `PascalCase`
Words are combined with first letter in each word capitalized. 
For an example: `YouAreBad`, `MeIsSuperior`, `EggIsGood`

4. `UPPER_SNAKE_CASE`
Words are all capitalized and combined with underscore sandwiched between words.
For an example: `LIFE_IS_BAD`, `I_AM_SPEAKING_THE_TRUTH`, `INVERTED_BINARY_TREE`

## File Name
Rules:
1. All directory names are `snake_case`. 
2. All filenames (`.c` files, `.md` files, `.h` files and etc.) are `PascalCase`. 
3. `.c` files that implements the header files must have the same name. 

## Headers
Basic rules:
1. Header guard's variable should be the file's name converted to `UPPER_SNAKE_CASE` (example: `HashTable.c` -> `_HASHTABLE_H_`, `LinkedList.c` -> `_LINKEDLIST_H_`). 
2. `include` statement for including header files must be at the top of the file (after header guard)
3. When including header files, `include` statments for `<>` and `""` is separated by one empty row. `include` statments for `<>` come first. 
4. After `include` statments, description of the header file must be written as multiline comment. 
5. The name of symbolic constant in `define` statements is in `UPPER_SNAKE_CASE`. 

Rules for declaration of `struct`:
1. All declaration of `struct` must use typedef (for the sake of convinience lmao).
2. All `struct` name must have prefix of `s_` (example: `s_HashTable`). The name should also be in `PascalCase`. 

Rules for declaration of `union`:
1. All declaration of `union` must use typedef (for the sake of convinience lmao).
2. All `union` name must have prefix of `u_` (example: `u_GP`). The name should also be in `PascalCase`. 
3. The name of 'properties' of a `union` must be its type (or something that describes its type like `string` for `char *`). It should also be in `UPPER_SNAKE_CASE`
4. Notes about whether a `union` should be stored as a pointer or value when storing it must be mentioned above the declaration as a singleline comment. 

Rules for declaration of `enum`:
1. All declaration of `enum` must use typedef (for the sake of convinience lmao).
2. All `enum` (include its value) must have prefix of `e_` (example: `e_days`). The name of `enum` (not the values) should be in `PascalCase`
3. The values' name must have shortened `enum`'s name as it prefix (if the name is already shortened, just use the name). The values' name and the prefix is separated with an underscore. 
**HOW TO SHORTEN A NAME**: Remove all the vowels, pick first two letter of each word, then make it all capitalized. (For an example: `HashTable` -> `HSTB`). 
4. The values' name is in `cammelCase`.

Rules for function declarations:
1. The function's name must have shortened current filename as it prefix. The function name and the prefix is separated with an underscore. 
**HOW TO SHORTEN A NAME**: Remove all the vowels, pick first two letter of each word, then make it all capitalized. (For an example: `HashTable` -> `HSTB`). 
2. The function's name is in `cammelCase`. 
3. Description for parameters and returned value must be written above the function declaration as a multiline comment. 

## .c Files
Basic rules:
1. When including header files, `include` statments for `<>` and `""` is separated by one empty row. `include` statments for `<>` come first. 
2. `define` statements is placed after the `include` statments. `include` statments and `define` statements are separated by one empty row. 
3. The name of symbolic constant in `define` statements is in `UPPER_SNAKE_CASE`. 

Rules for function implementation:
1. The function name and the prefix is separated with an underscore. 
2. The normal function's name (not static functions) must have shortened current filename as its prefix.
**HOW TO SHORTEN A NAME**: Remove all the vowels, pick first two letter of each word, then make it all capitalized. (For an example: `HashTable` -> `HSTB`). 
3. Static functions takes `T` as its prefix. 
4. Static functions must come before normal functions. 
5. The function's name is in `cammelCase`. 
6. Open curly bracket in new line for function only.
7. Local variable names are in `snake_case`. 
8. Control flow's open curly bracket not in new line. 

Rules for implementation of `struct`:
3. Description of each property of a `struct` must be written above the implementation as multiline comment. 
4. Names of properties are in `snake_case`. 
