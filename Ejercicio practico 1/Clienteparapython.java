import java.io.*;
import java.net.*;

public class Clienteparapython {

    public static void main(String[] args) {
        try {
            // Configura el cliente
            String host = "127.0.0.1";
            int portJava = 12345;
            int portPython = 6789;
            int portC = 1011;

            // Crea un socket TCP y conecta al servidor
            Socket socketJava = new Socket(host, portJava);
            Socket socketPython = new Socket(host, portPython);
            Socket socketC = new Socket(host, portC);

            // Establece flujos de entrada y salida
            BufferedReader entradaJava = new BufferedReader(new InputStreamReader(socketJava.getInputStream()));
            PrintWriter salidaJava = new PrintWriter(socketJava.getOutputStream(), true);

            BufferedReader entradaPython = new BufferedReader(new InputStreamReader(socketPython.getInputStream()));
            PrintWriter salidaPython = new PrintWriter(socketPython.getOutputStream(), true);

            BufferedReader entradaC = new BufferedReader(new InputStreamReader(socketC.getInputStream()));
            PrintWriter salidaC = new PrintWriter(socketC.getOutputStream(), true);
            // Crea un hilo para recibir mensajes del servidor
            Thread recibirThread = new Thread(() -> {
                try {
                    while (true) {
                        String mensaje = entradaJava.readLine();
                        if (mensaje == null) {
                            break;
                        }
                        System.out.println("Servidor: " + mensaje);
                    }
                } catch (IOException e) {
                    //e.printStackTrace();
                }
            });
            recibirThread.start();

            // Lee mensajes del usuario y los envía al servidor
            BufferedReader teclado = new BufferedReader(new InputStreamReader(System.in));
            String mensajeUsuario;
            while ((mensajeUsuario = teclado.readLine()) != null) {
                salidaJava.println(mensajeUsuario);
                salidaPython.println(mensajeUsuario);
                salidaC.println(mensajeUsuario);

            }

            // Cierra la conexión
            socketJava.close();
            socketPython.close();
            socketC.close();
        } catch (IOException e) {
            //e.printStackTrace();
        }
    }
}
