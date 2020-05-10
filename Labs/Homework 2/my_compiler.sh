#!/usr/bin/bash

FILE=$1

stack=()
prevSymbol=''

countSlash=0
commentFlag=0

balancedParanthesis='\(([^()]|(?R))*\)'
balancedCurlyBraces='\{([^{}]|(?R))*\}'

while IFS= read -r line 
do
    CL="$(echo -e "${line}" | tr -d '[:space:]')"

    for i in $(seq 1 ${#CL})
    do
        x=${CL:i-1:1}

        # Ignore comments
        if [[ $x == / ]]; then
            ((countSlash=countSlash+1))
            if [[ $countSlash == 2 ]]; then
                countSlash=0
                break
            fi
        fi

        # PUSH to stack
        if [[ $x == \{ || $x == \( || $x == \" || $x == \' ]]; then
            stack+=($x)
            echo PUSH $x
        fi

        # POP ) from stack
        if [[ $x == \) ]]; then
            if [[ ${#stack[@]} > 0 && ${stack[-1]} == \( ]]; then
                echo POP $x
                unset 'stack[${#stack[@]}-1]'
            else
                echo Unexpected \)
            fi
        fi

        # POP } from stack
        if [[ $x == \} ]]; then
            if [[ ${#stack[@]} > 0 && ${stack[-1]} == \{ ]]; then
                echo POP $x
                unset 'stack[${#stack[@]}-1]'
            else
                echo Unexpected \}
            fi
        fi

        # POP " from stack
        if [[ $x == \" ]]; then
            if [[ ${#stack[@]} > 0 && ${stack[-1]} == \" ]]; then
                echo POP $x
                unset 'stack[${#stack[@]}-1]'
            else
                echo Unexpected \"
            fi
        fi

        # POP " from stack
        if [[ $x == \' ]]; then
            if [[ ${#stack[@]} > 0 && ${stack[-1]} == \' ]]; then
                echo POP $x
                unset 'stack[${#stack[@]}-1]'
            else
                echo Unexpected \'
            fi
        fi

    done
done < "$FILE"

echo FINAL
for i in "${stack[@]}"
do
   echo $i
done