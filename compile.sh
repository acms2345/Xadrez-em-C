#!/bin/bash

echo "🎮 Compilando Xadrez em C para WebAssembly..."

# Cria a pasta docs se não existir
mkdir -p docs

# Compila os arquivos da pasta src para a pasta docs com ASYNCIFY
emcc src/menu.c src/xadrez.c src/jogadasvalidas.c \
    -o docs/xadrez.js \
    -s WASM=1 \
    -s ASYNCIFY=1 \
    -s ASYNCIFY_IMPORTS='["emscripten_sleep"]' \
    -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap","FS"]' \
    -s EXPORTED_FUNCTIONS='["_main"]' \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s EXIT_RUNTIME=0 \
    -s INVOKE_RUN=1 \
    -s MODULARIZE=0 \
    -s ENVIRONMENT=web \
    -O3

if [ $? -eq 0 ]; then
    echo "✅ Compilação concluída com sucesso!"
    echo "📁 Arquivos gerados em docs/:"
    echo "   - xadrez.js"
    echo "   - xadrez.wasm"
    echo ""
    echo "🌐 Para testar localmente:"
    echo "   cd docs && python -m http.server 8000"
else
    echo "❌ Erro na compilação"
    exit 1
fi