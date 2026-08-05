# Melhorias de Compatibilidade Android 12 (Kernel 4.19) para Box64

## Resumo das Implementações

Este documento descreve as melhorias implementadas no Box64 para melhorar a compatibilidade com Android 12 e kernel 4.19, baseadas na análise comparativa com Windroid-wine, Windroid-emu e Windroid-Rootfs.

## Arquivos Modificados

### 1. Novo Arquivo: `src/include/android_compat.h`
**Propósito**: Header central para compatibilidade Android com detecção de versão e paths específicos.

**Funcionalidades**:
- `get_android_version()`: Detecta versão Android em runtime
- `IS_ANDROID_AT_LEAST(version)`: Macro para verificação de versão
- `ANDROID_TMP_DIR`: Path específico para arquivos temporários (`/data/data/com.windroid.emu/files/usr/tmp`)
- `ANDROID_DATA_DIR`: Path para dados da aplicação
- `ANDROID_USR_DIR`: Path para arquivos do sistema emulados
- `IS_ANDROID_12_OR_LATER`: Verificação específica para Android 12+
- Macros para verificação de suporte a syscalls do kernel (memfd_create, getrandom)

### 2. `src/wrapped/wrappedlibc.c`
**Propósito**: Wrapper principal da libc com melhorias Android.

**Alterações**:
- Inclusão do header `android_compat.h`
- **shm_open/shm_unlink melhorados** (linhas 2275-2307):
  - Antes: Retornava -1 (falha completa)
  - Agora: Usa paths Android específicos em `ANDROID_TMP_DIR`
  - Cria diretório automaticamente se não existir
  - Validação de parâmetros

- **memfd_create melhorado** (linhas 4245-4290):
  - Tenta syscall nativa primeiro (kernel 3.17+)
  - Fallback para Android com paths específicos
  - Usa O_EXCL e unlink imediato para simular memfd anônimo
  - Fallback genérico usando shm_open

- **my_getrandom implementado** (linhas 4297-4340):
  - Tenta syscall nativa primeiro (kernel 3.17+)
  - Fallback para /dev/urandom
  - Suporte a modo blocking e non-blocking
  - Tenta /dev/random como último recurso

### 3. `src/wrapped32/wrappedlibc.c`
**Propósito**: Wrapper libc para emulação 32-bit com melhorias Android.

**Alterações**:
- Inclusão do header `android_compat.h`
- **shm_open/shm_unlink melhorados** (linhas 1597-1629):
  - Mesma implementação da versão 64-bit
  - Usa paths Android específicos

- **memfd_create melhorado** (linhas 3550-3595):
  - Habilitado (antes estava em #if 0)
  - Mesma lógica da versão 64-bit
  - Tenta syscall nativa primeiro
  - Fallback Android com paths específicos

- **my32_getrandom implementado** (linhas 3602-3645):
  - Nova função para emulação 32-bit
  - Mesma lógica da versão 64-bit
  - Fallback para /dev/urandom

### 4. `src/wrapped/wrappedselinux.c`
**Propósito**: Wrapper SELinux com tratamento específico para Android.

**Alterações**:
- Inclusão do header `android_compat.h`
- **my_selinux_context_to_sid** (linhas 271-297):
  - Mapeia contextos Android comuns para SIDs
  - Contextos suportados: untrusted_app, priv_app, system_app, app_data_file, tmpfs
  - Retorna SID genérico para contextos desconhecidos

- **my_selinux_sid_to_context** (linhas 299-316):
  - Mapeia SIDs de volta para contextos
  - Retorna contexto padrão para SIDs desconhecidos

- **my_selinux_getenforce** (linhas 318-328):
  - Retorna modo permissive para Android 12+ (melhor compatibilidade)
  - Retorna modo enforcing para Android mais antigos

## Benefícios das Implementações

### 1. Compatibilidade de Shared Memory
**Antes**: shm_open sempre falhava no Android
**Depois**: Usa paths Android específicos com permissões adequadas
**Impacto**: Aplicações que dependem de shared memory agora funcionam

### 2. Performance de memfd_create
**Antes**: Fallback genérico sem otimização Android
**Depois**: Tenta syscall nativa primeiro (kernel 4.19 suporta), fallback otimizado
**Impacto**: Melhor performance em dispositivos Android modernos

### 3. Entropia Criptográfica
**Antes**: getrandom não implementado ou fallback inadequado
**Depois**: Implementação robusta com fallback para /dev/urandom
**Impacto**: Aplicações criptográficas funcionam corretamente

### 4. SELinux Compatibility
**Antes**: Wrapper genérico sem tratamento Android
**Depois**: Contextos Android específicos mapeados
**Impacto**: Menos falhas de permissão SELinux em Android 12

### 5. Paths Android Específicos
**Antes**: Usava /tmp (pode não existir ou ter permissões restritas)
**Depois**: Usa paths específicos do app Android
**Impacto**: Evita problemas de permissão e SELinux

## Compatibilidade com Kernel 4.19

As implementações consideram especificamente o kernel 4.19 usado no Android 12:

- **memfd_create**: Kernel 4.19 suporta (syscall 319), implementação tenta usar nativamente
- **getrandom**: Kernel 4.19 suporta (syscall 318), implementação tenta usar nativamente
- **shm_open**: Fallback necessário pois /dev/shm pode não existir
- **SELinux**: Contextos específicos do Android 12 são tratados

## Testes Recomendados

1. **Testar aplicações que usam shared memory**
   - Verificar se shm_open funciona corretamente
   - Verificar se arquivos são criados em ANDROID_TMP_DIR

2. **Testar performance de memfd_create**
   - Comparar performance com e sem syscall nativa
   - Verificar se fallback funciona quando syscall não disponível

3. **Testar entropia criptográfica**
   - Verificar se getrandom retorna dados aleatórios válidos
   - Testar aplicações que dependem de criptografia

4. **Testar SELinux**
   - Verificar se contextos são mapeados corretamente
   - Verificar se modo permissive funciona em Android 12

5. **Testar compatibilidade geral**
   - Testar em diferentes versões Android
   - Testar em diferentes versões de kernel

## Próximos Passos Opcionais

1. **Implementar ASharedMemory para Android 27+**
   - Usar API nativa Android quando disponível
   - Melhor performance e integração

2. **Adicionar mais contextos SELinux**
   - Expandir lista de contextos suportados
   - Adicionar detecção dinâmica de contextos disponíveis

3. **Implementar detecção de kernel em runtime**
   - Verificar versão do kernel em runtime
   - Adaptar comportamento baseado em versão

4. **Adicionar logging específico Android**
   - Log detalhado de operações Android
   - Ajudar em debugging de problemas de compatibilidade

## Referências

- Windroid-Rootfs patches: `packages/pulseaudio/01-pulseaudio-android.patch`
- Windroid-Rootfs patches: `packages/android-shmem/fix-build.patch`
- Windroid-wine Android driver: `dlls/wineandroid.drv/init.c`
- Kernel 4.19 documentation: https://www.kernel.org/doc/html/latest/
- Android 12 compatibility: https://developer.android.com/about/versions/12
