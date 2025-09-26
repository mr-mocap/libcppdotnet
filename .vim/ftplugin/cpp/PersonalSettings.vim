" No tabs & tabstop at 4
setlocal tabstop=4
setlocal shiftwidth=4
setlocal expandtab

" Indenting
setlocal smartindent
setlocal autoindent
setlocal cindent

" Allow for C++20 Module imports like:
" import <vector>;
setlocal include=^\s*#\s*include\|^\s*import\s*\|^\s*export\s*import\s*\
