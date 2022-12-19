#!/bin/bash

../pipex "test_in" "cat -e" "rev" "test_out1"
< test_in cat -e | rev >test_out1_cmp
echo "heredoc delimiter is END"
../pipex here_doc END "tr '[:lower:]' '[:upper:]'" "tr 'I' '\!'"  "tr 'E' '3'" "tr 'O' '0'" "test_out2"
../pipex test_in "ls -la /Users/jsubel/Cursus/pipex/src" "grep jsubel" "cat -e" "wc -w" "test_out3"
< test_in ls -la /Users/jsubel/Cursus/pipex/src | grep jsubel | cat -e | wc -w >test_out3_cmp