#!/usr/bin/bash

FILE=$1

regexFindFunc='[0-9]+[a-f]* <[a-z|A-Z]+>:'
regexFindLine='[a-z][a-z][a-z]+'

declare -A instructions
numInstructions=0

functions=()
numFunction=0

tmpLine=''
tmpKey=''
tmpName=''
tmpAddr=''

# Read every line in the passed file
while IFS= read -r line 
do

  tmpLine=$line

  # Check if line is instruction
  if [[ $tmpLine =~ $regexFindLine ]]; then

    # Get instruction name
    [[ $tmpLine =~ $'\t'[a-z][a-z][a-z|0-9]+ ]] && tmpKey=${BASH_REMATCH[0]}

    # Increment count or add new entry to instructions dictionary
    if [ -n "$tmpKey" ] && [[ ${instructions[$tmpKey]} ]]; then 
      ((instructions[$tmpKey]=${instructions[$tmpKey]}+1))
    else
      [ -n "$tmpKey" ] && instructions[$tmpKey]=1
      [ -n "$tmpKey" ] && ((numInstructions=numInstructions+1))
    fi

  fi

  # Check if line is a source code function
  if [[ $tmpLine =~ $regexFindFunc ]]; then

    # Get function name with <>
    [[ $tmpLine =~ \<[a-z]+\> ]] && tmpName=${BASH_REMATCH[0]}

    # Remove <> from name
    [[ $tmpName =~ [a-z]+ ]] && tmpName=${BASH_REMATCH[0]}

    # Remove trailing ceros from address
    [[ $tmpLine =~ [1-9|a-f][0-9|a-f]+ ]] && tmpAddr=${BASH_REMATCH[0]}

    # Add entry to functions array
    functions+=($tmpName' : Located at '$tmpAddr' addr')
    ((numFunction=numFunction+1))

  fi

done < "$FILE"


echo Hi, this is the output of the analysis:

echo ' ' You have $numInstructions kinds of instructions in this object file:
for K in "${!instructions[@]}"; do 
  echo '   ' $K : Executed ${instructions[$K]} times 
done

echo ' ' You have $numFunction functions:
for i in "${functions[@]}"
do
   echo '    '$i
done



