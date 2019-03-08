#include "cone.h"
#include "writetofile.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>



/**
 * Esta função, dado um raio, uma altura, um número de slices e de stacks e
 * um nome de um ficheiro, gera todos os vértices necessários para a
 * formação de triângulos, que juntos formarão um cone. Os vértices gerados
 * serão guardados num ficheiro .3d
 * @param botRad Raio da base do cone;
 * @param slices Número de slices (cortes verticais) do cone;
 * @param stacks Número de stacks (cortes horizontais) do cone;
 * @param fname Nome do ficheiro onde serão guardados os vértices gerados;
 * O número de triângulos que serão usados para a
 * base do cone é proporcional ao número de slices fornecidas, enquanto
 * que o número de triângulos necessários para a superfície lateral é proporcional
 * ao número de stacks e slices
 */
int createCone(float botRad, float height, int slices, int stacks, char * fname){
    FILE * file = openFile(fname);
    if (slices < 0 || stacks < 0)
        return 1;

    float angle=(float) 2*M_PI/slices;
    float division=height/stacks;
    float baseY = height/2;


    for(int i=0; i<slices; i++) {

        //   Centro
        //  /      \
        // b2      b1
        float bx1 = botRad * cos(i * angle);
        float bz1 = botRad * sin(i * angle);

        float bx2 = botRad * cos((i + 1) * angle);
        float bz2 = botRad * sin((i + 1) * angle);

        // base triangle
        writeToFile(0.0f, 0.0f - baseY, 0.0f, file);
        writeToFile(bx1, 0.0f - baseY, bz1, file);
        writeToFile(bx2, 0.0f - baseY, bz2, file);


        for (int j = 0; j < stacks; j++) {

            //radius for j stacks
            float div = (float) j / stacks;
            float radiusD = (float) (1.0 - (div)) * botRad;

            //radius for j+1 stacks
            div = (float) (j + 1) / stacks;
            float radiusU = (float) (1.0 - (div)) * botRad;

            //d -> level j
            //u -> level j+1
            // ux2 -- ux1
            //  |      |
            //  |      |
            // dx2 -- dx1

            // coordinates of the vertex that is on the right and bottom
            float dx1 = radiusD * cos(i * angle);
            float dz1 = radiusD * sin(i * angle);

            // coordinates of the vertex that is on the left and bottom
            float dx2 = radiusD * cos((i + 1) * angle);
            float dz2 = radiusD * sin((i + 1) * angle);

            // coordinates of the vertex that is on the right and up
            float ux1 = radiusU * cos(i * angle);
            float uz1 = radiusU * sin(i * angle);

            // coordinates of the vertex that is on the left and up
            float ux2 = radiusU * cos((i + 1) * angle);
            float uz2 = radiusU * sin((i + 1) * angle);

            float dy = j * division - baseY;
            float uy = (j + 1) * division - baseY;

            // one triangle [dx1,ux1,dx2]
            writeToFile(dx1, dy, dz1, file);
            writeToFile(ux1, uy, uz1, file);
            writeToFile(dx2, dy, dz2, file);

            //another triangle [dx2,ux1,ux2]
            writeToFile(dx2, dy, dz2, file);
            writeToFile(ux1, uy, uz1, file);
            writeToFile(ux2, uy, uz2, file);

        }
    }
    return 0;
}