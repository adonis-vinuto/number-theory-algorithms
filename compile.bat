@echo off
REM ========================================
REM  GCD Algorithm Analyzer - Windows Build
REM  Arquivo: compile.bat
REM ========================================

echo ========================================
echo  Compilando GCD Algorithm Analyzer
echo ========================================

REM Verificar se GCC está disponível
echo Verificando compilador...
gcc --version >nul 2>&1
if errorlevel 1 (
    echo.
    echo ❌ ERRO: GCC nao encontrado!
    echo.
    echo Para instalar MinGW-w64:
    echo 1. Via Chocolatey ^(como Admin^):
    echo    choco install mingw
    echo.
    echo 2. Download direto:
    echo    https://www.mingw-w64.org/downloads/
    echo.
    pause
    exit /b 1
)

echo ✓ GCC encontrado

REM Verificar se os arquivos fonte existem
echo.
echo Verificando arquivos fonte...

set "missing_files="

if not exist "src\interfaces\cli\main.c" (
    echo ✗ src\interfaces\cli\main.c
    set "missing_files=1"
) else (
    echo ✓ src\interfaces\cli\main.c
)

if not exist "src\interfaces\cli\command_parser.c" (
    echo ✗ src\interfaces\cli\command_parser.c
    set "missing_files=1"
) else (
    echo ✓ src\interfaces\cli\command_parser.c
)

if not exist "src\core\orchestration\system_coordinator.c" (
    echo ✗ src\core\orchestration\system_coordinator.c
    set "missing_files=1"
) else (
    echo ✓ src\core\orchestration\system_coordinator.c
)

if not exist "challenge_implementation.c" (
    echo ✗ challenge_implementation.c ^(arquivo necessario - deve estar na raiz^)
    set "missing_files=1"
) else (
    echo ✓ challenge_implementation.c
)

if defined missing_files (
    echo.
    echo ❌ ERRO: Arquivos fonte faltando!
    echo Verifique se a estrutura do projeto esta correta.
    pause
    exit /b 1
)

echo ✓ Todos os arquivos fonte encontrados

REM Limpar arquivos antigos
echo.
echo Limpando arquivos antigos...
if exist "gcd_analyzer.exe" del "gcd_analyzer.exe"
if exist "*.o" del "*.o"
echo ✓ Limpeza concluida

REM Compilar o projeto
echo.
echo ========================================
echo  Iniciando compilacao...
echo ========================================

gcc -Wall -Wextra -O2 -std=c99 -o gcd_analyzer.exe ^
    "src\interfaces\cli\main.c" ^
    "src\interfaces\cli\command_parser.c" ^
    "src\core\orchestration\system_coordinator.c" ^
    "src\challenges\greatest_common_divisor\challenge_services\solution_registry.c" ^
    "src\challenges\greatest_common_divisor\challenge_services\mdc_analyzer.c" ^
    "src\challenges\greatest_common_divisor\solutions\euclidean_family\implementations\classic.c" ^
    "src\challenges\greatest_common_divisor\solutions\euclidean_family\implementations\recursive.c" ^
    "src\challenges\greatest_common_divisor\solutions\binary_family\implementations\stein.c" ^
    "src\infrastructure\utilities\math_utils.c" ^
    "src\infrastructure\utilities\memory_utils.c" ^
    "challenge_implementation.c"

REM Verificar se a compilação foi bem-sucedida
if exist "gcd_analyzer.exe" (
    echo.
    echo ✅ Compilacao bem-sucedida!
    echo ✅ Executavel criado: gcd_analyzer.exe
    
    REM Verificar tamanho do arquivo
    for %%I in ("gcd_analyzer.exe") do echo ✓ Tamanho: %%~zI bytes
    
    echo.
    echo ========================================
    echo  Testando o programa
    echo ========================================
    echo.
    echo Executando teste basico...
    echo.
    
    REM Teste simples
    "gcd_analyzer.exe" compare 48 18
    
    if errorlevel 1 (
        echo.
        echo ⚠️  Programa compilou mas teve erro na execucao
        echo Tente executar manualmente: gcd_analyzer.exe help
    ) else (
        echo.
        echo ✅ Teste basico passou!
    )
    
) else (
    echo.
    echo ❌ ERRO na compilacao!
    echo.
    echo Possiveis causas:
    echo - Arquivos fonte com erros de sintaxe
    echo - Paths incorretos dos arquivos
    echo - Compilador mal configurado
    echo.
    echo Tente compilar com mais detalhes usando:
    echo gcc -v -Wall -Wextra -O2 -std=c99 -o gcd_analyzer.exe [arquivos...]
    pause
    exit /b 1
)

echo.
echo ========================================
echo  🎉 PRONTO PARA USAR!
echo ========================================
echo.
echo Comandos disponiveis:
echo.
echo   gcd_analyzer.exe help              # Mostrar ajuda completa
echo   gcd_analyzer.exe list              # Listar algoritmos disponiveis
echo   gcd_analyzer.exe compare 48 18     # Comparar todos os algoritmos
echo   gcd_analyzer.exe execute -a stein 48 18  # Executar algoritmo especifico
echo   gcd_analyzer.exe extended 48 18    # Algoritmo Euclidiano Estendido
echo   gcd_analyzer.exe fastest 48 18     # Encontrar algoritmo mais rapido
echo   gcd_analyzer.exe interactive       # Modo interativo
echo   gcd_analyzer.exe benchmark -i 5000 48 18  # Benchmark detalhado
echo.
echo Exemplos de uso interessantes:
echo   gcd_analyzer.exe compare 1000000 999999    # Numeros grandes
echo   gcd_analyzer.exe fastest 12345 6789        # Ver qual e mais rapido
echo   gcd_analyzer.exe extended 240 46           # Ver coeficientes de Bezout
echo.
echo Para executar, use: .\gcd_analyzer.exe [comando]
echo (O .\ e necessario no PowerShell)
echo.
pause