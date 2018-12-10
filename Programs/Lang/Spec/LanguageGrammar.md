program: imports outer-body

outer-body:     decorator inner-body

decorator:      '@' ident arg-call-list

arg-call-list:      '(' ')' | 
                    '(' arg-call-body ')'

arg-call-body:      ident | 
                    ident ',' arg-call-body | 
                    kwarg-call-body

kwarg-call-body:    ident '=' expr | 
                    ident '=' expr ',' kwarg-call-body

inner-body:     function body | 
                variable body | 
                class body

function:       'def' ident arg-list '->' type func-body

arg-list:       '(' ')' | 
                '(' arg-body ')'

arg-body:       ident ':' type | 
                ident ':' type ',' arg-body |
                ident ':' type '=' expr |
                ident ':' type '=' expr ',' default-arg-body

default-arg-body:   ident ':' type '=' expr | 
                    ident ':' type '=' expr ',' default-arg-body

func-body:      '{' stmt '}'

stmt:           return-stmt stmt | 
                if-stmt stmt | 
                branch-stmt stmt |
                for-stmt stmt |
                while-stmt stmt |
                var-decl stmt

var-decl:       'var' ident '=' expr

while-stmt:     'while' bool-expr func-body

for-stmt:       'for' for-body func-body

for-body:       ident 'in' expr

branch-stmt:    'branch' branch-body

branch-body:    '{' branch-options '}'

branch-options: expr '->' func-body |
                expr '->' func-body branch-options |
                'else' '->' func-body

return-stmt:    'return' expr

if-stmt:        'if' bool-stmt func-body |
                'if' bool-stmt func-body else-stmt |
                'if' bool-stmt func-body elif-stmt

elif-stmt:      'else' 'if' bool-stmt func-body |
                'else' 'if' bool-stmt func-body elif-stmt |
                'else' 'if' bool-stmt func-body else-stmt

imports:    import-stmt imports | 
            import-stmt

import-stmt:    extern-import | 
                native-import

native-import: 'import' dotted-path exposing-list

extern-import: 'extern' lang 'import' dotted-path exposing-list |
               'extern' lang 'import' dotted-path exposing-list

exposing-import:    '{' '...' '}' |
                    '{' import-list '}'

import-list:    ident | 
                ident ',' import-list
