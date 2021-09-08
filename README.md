# ModeloDocumento-ProjetoEngenharia-ProgramacaoPratica
Projeto de engenharia - Simulador de condução térmica em objetos 3D com perfis genéricos

O seguinte projeto de engenharia deve simular a difusão térmica de qualquer objeto tridimensional, onde o usuário desenha a superfície de alguns perfis e escolhe as temperaturas e suas propriedades termofísicas. A equação do Calor será modelada por diferenças finitas pelo modelo BTCS, utilizando fronteiras de Neumann, e a programação utilizará paralelismo e multithreading para acelerar as simulações. No quesito prático, o usuário poderá desenhar a superfície a ser simulada, escolher sua temperatura, propriedades termofísicas e se é fonte/sumidouro ou não. Também terá a liberdade de escolher um ponto para analisar os gráficos da evolução térmica no tempo e espaço, salvar as superfícies dos perfis e carregar essas camadas com todas as suas propriedades e modificá-las. Por fim, o projeto será utilizado para estudar a injeção de calor em reservatórios 2D e 3D, e avaliar a distribuição da temperatura ao longo do tempo no reservatório.

Últimas implementações:
- perfis para simulação 3D: o usuário pode desenhar vários perfis, e eles ficam salvos na classe simulador;
- adaptação das operações para o 3D: os perfis estão conectados e podem transferir calor;
- implementação do paralelismo: o simulador utiliza 1 thread para gerar os gráficos, e uma thread por perfil;
- opção de paralelismo: o usuário pode escolher se quer utilizar o paralelismo ou não.

ToDo:
- gerar gráficos ao longo do espaço;
- salvar o vetor de grid e carregar esse vetor;
- implementar interface amigável com Qt;
- tentar desenvolver a equação para aumentar o espaço entre perfis;
- salvar resultados em arquivo pdf;