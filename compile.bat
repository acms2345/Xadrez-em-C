@echo off
echo Compilando Xadrez em C para WebAssembly...

REM Cria a pasta docs se nao existir
if not exist docs mkdir docs

REM Compila os arquivos da pasta src para a pasta docs
"C:\Users\Antonio Carlos\emsdk\upstream\emscripten\emcc.bat" src/menu.c src/xadrez.c src/jogadasvalidas.c -o docs/xadrez.js -s WASM=1 -s EXPORTED_RUNTIME_METHODS=['ccall','cwrap','FS'] -s EXPORTED_FUNCTIONS=['_main'] -s ALLOW_MEMORY_GROWTH=1 -s EXIT_RUNTIME=0 -s INVOKE_RUN=1 -s MODULARIZE=0 -s ENVIRONMENT=web -O3

if %ERRORLEVEL% EQU 0 (
    echo Compilacao concluida com sucesso!
    echo Arquivos gerados em docs/:
    echo    - xadrez.js
    echo    - xadrez.wasm
) else (
    echo Erro na compilacao
    exit /b 1
)