import-body:        ident |
                    ident ',' import-body

import-list:        '{' import-body '}'

import-path:        ident |
                    ident '::' import-path

import:             'import' import-path |
                    'import' import-path import-list

imports:            import | 
                    import imports

decorator-path:     ident |
                    ident '::' decorator-path

number:             int |
                    float

const:              string |
                    ident |
                    char |
                    number

bin-op:             '+'  |
                    '+=' |
                    '-'  |
                    '-=' |
                    '*'  |
                    '*=' |
                    '/'  |
                    '/=' |
                    '%'  |
                    '%=' |
                    '&'  |
                    '&=' |
                    '|'  |
                    '|=' |
                    '^'  |
                    '^='

bin-expr:           expr bin-op expr

bool-op:            'and' | '&&' |
                    'or'  | '||' |
                    '=='  | 'is' |
                    '!='  | 'is' 'not' |
                    '>'   | '>=' |
                    '<'   | '<=' |
                    'in'  | 'not' 'in'

bool-single-op:     '!'

single-bool-expr:   bool-single-op expr

bool-expr:          expr bool-op expr

dotted-class-name:  ident |
                    ident '.' ident

dotted-name:        ident |
                    ident '::' dotted-name |
                    dotted-class-name

arg-list:           '(' arg-body ')'

func-call:          dotted-name arg-list 

expr:               const |
                    bin-expr |
                    single-expr |
                    bool-expr |
                    single-bool-expr |
                    func-call |
                    ternary-expr |
                    assign-expr |
                    '(' expr ')'

kwarg-list:         ident '=' expr |
                    ident '=' expr ',' kwarg-list

arg-list:           arg |
                    arg ',' arg-list |
                    arg ',' kwarg-list |
                    kwarg ',' kwarg-list 

decorator-args:     '(' arg-list ')'

decorator:          '@' decorator-path |
                    '@' decorator-path decorator-args

decorators:         decorator |
                    decorator decorators

preamble:           decorators | 
                    decorators imports | 
                    imports

program:            preamble body | 
                    body