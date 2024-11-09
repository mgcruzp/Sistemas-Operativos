/****************************************************************
                  Pontificia Universidad Javeriana
     Autor: G. Cruz
     Fecha: Noviembre 2024
     Materia: Sistemas Operativos
     Tema: Taller de Evaluación de Rendimiento
     Fichero: script automatización ejecución por lotes 
****************************************************************/

$Path = `pwd`;
chomp($Path);

$Nombre_Ejecutable = "MM_ejecutable";
@Size_Matriz = ("200", "300");     # Tamaños de matriz
@Num_Hilos = (1, 2);               # Número de hilos
$Repeticiones = 30;                # 30 repeticiones para cada configuración

# Para cada tamaño de matriz
foreach $size (@Size_Matriz) {
    
    # Para cada número de hilos
    foreach $hilo (@Num_Hilos) {
        
        # Nombre del archivo de salida
        $file = "$Path/$Nombre_Ejecutable-" . $size . "-Hilos-" . $hilo . ".dat";
        
        # Abre el archivo en modo escritura
        open(my $fh, '>', $file) or die "No se pudo abrir el archivo $file: $!";
        
        # Bucle para ejecutar el experimento 30 veces
        for ($i = 0; $i < $Repeticiones; $i++) {
            
            # Ejecuta el programa y captura el tiempo de ejecución
            my $output = `$Path/$Nombre_Ejecutable $size $hilo`;
            
            # Almacena el resultado en el archivo
            print $fh "$output\n";
        }
        
        # Cierra el archivo después de todas las repeticiones
        close($fh);
        
        # Calcula el promedio de los resultados
        calcular_promedio($file);
    }
}

# Función para calcular el promedio de los valores en un archivo
sub calcular_promedio {
    my ($filename) = @_;
    open(my $fh, '<', $filename) or die "No se pudo abrir el archivo $filename: $!";
    
    my $suma = 0;
    my $contador = 0;
    
    # Lee cada línea y suma los valores
    while (my $line = <$fh>) {
        chomp($line);
        $suma += $line;
        $contador++;
    }
    
    # Calcula el promedio
    my $promedio = $suma / $contador;
    close($fh);
    
    # Almacena el promedio en un archivo de resultados
    my $resultado_file = "$filename-promedio.dat";
    open(my $result_fh, '>', $resultado_file) or die "No se pudo abrir el archivo $resultado_file: $!";
    print $result_fh "Promedio: $promedio\n";
    close($result_fh);
}
