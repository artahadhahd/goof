# Description
Statically and strongly typed, interpreted language

# Syntax

### Functions
```
add(a, b) :: Int, Int -> Int {
    return a + b;
}
```
```
add(a, b) :: T, T -> T {
    return a + b;
}
```
```
add(a, b) :: T, T -> T {
    return a + b;
}
```
```
add(a, b) :: T, T -> T if T can Add {

}
```

infixl 2 can(f: Func) {

}
```
add(a, b) :: T, T -> T if a % 2 == 0, if T can Add {

}
```

function(a, b) :: T, T -> int
    if T can Add
{
    x = 2 :: Float
    y = x + 6 :: Int
} else if T can Subtract {

} else {

}

### interfaces
```
function Add {
    operator +(lhs, rhs) :: T, T -> T;
}
```
