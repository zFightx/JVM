# ./testClasses.ps1 

function testClass($file, $noClear){
    Write-Output "Testing class $file"	
    Pause
    ./main $file
    Pause
    Write-Output "Testing class $file with java"
    Pause
    $javaCommandFile = $file.Replace(".class", "")
    java $javaCommandFile
    Pause

    if (!$noClear){
        Clear-Host
    }
}

if ($args[0] -eq 0 ) {
    Write-Output "Compilando..."
    g++ -o main -std=c++11 Leitor.cpp ./src/*.cpp
    Write-Output "Pronto!"
}

if ($null -ne $args[1]){
    testClass $args[1] clear
    Write-Output "Fim :D"
    Exit
}



# ./main soma_certo.class
# Pause
# ./main Pig.class
# Pause
# ./main .\Point.class
# Pause
testClass multi_sem_string.class

# testClass method_test.class       // string buffer

testClass Mercado.class

testClass lookupswitch.class

testClass long_cast.class

testClass Goo.class

# testClass FooCorporation.class    // classe Empregado ausente

testClass Foo.class

testClass double_aritmetica.class


Write-Output "Fim :D"
