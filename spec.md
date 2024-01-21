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
```
add(a, b) :: T, T -> T if a % 2 == 0, if T can Add {

}
```

### interfaces
```
function Add {
    operator +(lhs, rhs) :: T, T -> T;
}
```
