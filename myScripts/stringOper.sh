myVar="Hello Sanket!"
length=${#myVar}

echo "String : ${myVar[*]}"

echo "Upper case : ${myVar^^}"
echo "Lower cae : ${myVar,,}"

echo "Length : $length"

# To replace a string
newVar=${myVa/Sanket/Disale}

echo "New Name : ${newVar}"

# To slice a string

echo "After Slice ${myVar:6:6}"

