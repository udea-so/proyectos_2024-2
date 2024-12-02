import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.concurrent.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class TSP {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        int numCiudades = 12;
        int rangoDistancias = 100;

        int numProcesadores = 4;
        // int numProcesadores = Runtime.getRuntime().availableProcessors();
        System.out.println("Número de núcleos de CPU disponibles: " + numProcesadores);

        int[][] distancias = generarMatrizDistancias(numCiudades, rangoDistancias);

        // Ejecución secuencial
        long inicioSecuencial = System.currentTimeMillis();
        int resultadoSecuencial = tspSecuencial(distancias);
        long finSecuencial = System.currentTimeMillis();
        System.out.println("Distancia mínima (secuencial): " + resultadoSecuencial);
        System.out.println(
                "Tiempo de ejecución (secuencial): " + (finSecuencial - inicioSecuencial) / 1000.0 + " segundos");

        // Ejecución paralela
        long inicioParalelo = System.currentTimeMillis();
        int resultadoParalelo = tspParalelo(distancias, numProcesadores);
        long finParalelo = System.currentTimeMillis();
        System.out.println("Distancia mínima (paralelo): " + resultadoParalelo);
        System.out.println("Tiempo de ejecución (paralelo): " + (finParalelo - inicioParalelo) / 1000.0 + " segundos");
    }

    public static int[][] generarMatrizDistancias(int numCiudades, int rangoDistancias) {
        Random random = new Random();
        int[][] matriz = new int[numCiudades][numCiudades];
        for (int i = 0; i < numCiudades; i++) {
            for (int j = i + 1; j < numCiudades; j++) {
                int distancia = random.nextInt(rangoDistancias - 1) + 1;
                matriz[i][j] = distancia;
                matriz[j][i] = distancia;
            }
        }
        return matriz;
    }

    public static int tspSecuencial(int[][] distancias) {
        List<Integer> ciudades = IntStream.range(0, distancias.length).boxed().collect(Collectors.toList());
        int minDistancia = Integer.MAX_VALUE;

        System.out.println("Ciudades Secuencial" + ciudades);
        for (int[] fila : distancias) {
            for (int columna : fila) {
                System.out.print(columna + "\t");
            }
            System.out.print("\n");
        }
        List<List<Integer>> permutaciones = getPermutaciones(ciudades);

        for (List<Integer> permutacion : permutaciones) {
            int distTotal = calcularDistancia(permutacion, distancias);
            minDistancia = Math.min(minDistancia, distTotal);
        }
        return minDistancia;
    }

    public static int calcularDistancia(List<Integer> permutacion, int[][] distancias) {
        int distTotal = 0;
        for (int i = 0; i < permutacion.size() - 1; i++) {
            distTotal += distancias[permutacion.get(i)][permutacion.get(i + 1)];
        }
        distTotal += distancias[permutacion.get(permutacion.size() - 1)][permutacion.get(0)];
        return distTotal;
    }

    public static int tspParalelo(int[][] distancias, int numProcesos) throws InterruptedException, ExecutionException {
        List<Integer> ciudades = IntStream.range(0, distancias.length).boxed().collect(Collectors.toList());
        ExecutorService executor = Executors.newFixedThreadPool(numProcesos);

        System.out.println("Ciudades paralelo" + ciudades);
        for (int[] fila : distancias) {
            for (int columna : fila) {
                System.out.print(columna + "\t");
            }
            System.out.print("\n");
        }

        List<Future<Integer>> resultados = new ArrayList<>();
        List<List<Integer>> permutaciones = getPermutaciones(ciudades);
        for (List<Integer> permutacion : permutaciones) {
            resultados.add(executor.submit(() -> calcularDistancia(permutacion, distancias)));
        }

        int minDistancia = Integer.MAX_VALUE;
        for (Future<Integer> resultado : resultados) {
            minDistancia = Math.min(minDistancia, resultado.get());
        }

        executor.shutdown();
        return minDistancia;
    }

    public static List<List<Integer>> getPermutaciones(List<Integer> ciudades) {
        // System.out.println("Permutaciones");
        if (ciudades.isEmpty())
            return Collections.singletonList(new ArrayList<>());
        List<List<Integer>> permutaciones = new ArrayList<>();
        Integer primeraCiudad = ciudades.remove(0);
        List<List<Integer>> subPermutaciones = getPermutaciones(ciudades);
        for (List<Integer> subPermutacion : subPermutaciones) {
            for (int i = 0; i <= subPermutacion.size(); i++) {
                List<Integer> nuevaPermutacion = new ArrayList<>(subPermutacion);
                nuevaPermutacion.add(i, primeraCiudad);
                permutaciones.add(nuevaPermutacion);
                // System.out.println(nuevaPermutacion);
            }
        }
        ciudades.add(0, primeraCiudad);
        return permutaciones;
    }
}
