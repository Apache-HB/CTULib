
char:                       [a-z] | [A-Z]

ident-letters:              char | [0-9] | '_'

ident-body:                 ident-letters |
                            ident-letters ident-body

ident:                      char |
                            char ident-body

dotted-name(pattern):       ident |
                            ident pattern dotted-name(pattern)

num-lit:                    integer |
                            float |
                            hexidecimal |
                            binary

constant:                   bool-lit |
                            num-lit |
                            str-lit |
                            char-lit |
                            list-lit |
                            dict-lit

binary-op:                  '-' expr                

binary-op:                  '+' | '-' | '*' | '%' | '/'

bi-op:                      expr binary-op expr

expr:                       constant |
                            unary-op |
                            bi-op |
                            func-call |
                            '(' expr ')'

kwarg-call-body:            ident '=' expr |
                            ident '=' expr ',' kwarg-call-body

arg-call-body:              expr |
                            expr ',' arg-call-body |
                            expr ',' kwarg-call-body |
                            kwarg-call-body

arg-call-list:              '(' ')' |
                            '(' arg-call-body ')'

decorator:                  '@' dotted-name('::') |
                            '@' dotted-name('::') arg-call-list

preamble:                   decorator | 
                            decorator imports | 
                            imports

program:                    preamble body

#todo all of this