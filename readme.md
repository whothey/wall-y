Robô Computação Gráfica
=============================================

## Alunos

- Gabriel Henrique Rudey
- Ricardo Augusto Müller

## Cameras

Existem duas cameras, a camera do robo, controlada com WASD e +- e a camera do teto, a segunda
sempre segue o robô, e sua movimentaçao só pode ser feita com + e -, já que as outras coordenadas
são definidas pelo robô;

## Compilando

Na pasta `src`:

```sh
make      # Compila
make exec # Compila e roda
```

## Comandos

Lista de comandos

 - `TAB` troca a câmera atual (robô/labirinto).
 - `R` ou `r` troca o controle para o robô.
 - `C` ou `c` troca o controle para a câmera.
 - `W` move o objeto sob controle para frente OU a camera no eixo Z.
 - `A` rotaciona o objeto sob controle para a esquerda OU move a camera no eixo X.
 - `S` move o objeto sob controle para tras OU a camera no eixo Z (negativo).
 - `D` rotaciona o objeto sob controle para a direita OU move a camera no eixo X (negativo).
 - `↑` move a camera no eixo Y.
 - `↓` move a camera no eixo Y (negativo).
