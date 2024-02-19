import java.nio.charset.StandardCharsets;
import javax.net.ssl.*;
import java.util.ArrayList;
import java.util.Base64;
import java.io.*;

/*
 * User 클래스 : 사용자 정보
 */
class User {
    String username;    // ID
    String password;    // PASSWORD
    String sender;      // sender

    User(String username, String password, String sender) {
        this.username = username;
        this.password = password;
        this.sender = sender;
    }

    void setUsername(String username) {
        this.username = username;
    }
    void setPassword(String password) {
        this.password = password;
    }
    void setSender(String sender) {
        this.sender = sender;
    }
}

/*
 * SocketMaker 클래스 : 소켓 생성 및 명령 전송
 */
class SocketMaker {
    class Header {
        String From;
        String To;
        String Subject;
    }
    public Header header = new Header();
    public String body;
    public BufferedReader inFromServer;
    public PrintWriter printWriter;
    public SSLSocket socket;
    public String line;
    public SocketMaker(String smtpServer, int smtpServerPort, User user, String recipient, String subject, String content) throws IOException {

        // 1. SMTP 서버에 소켓 연결
        SSLSocketFactory sslSocketFactory = (SSLSocketFactory) SSLSocketFactory.getDefault();
        this.socket = (SSLSocket) sslSocketFactory.createSocket(smtpServer, smtpServerPort);

        // Header 설정
        this.header.From = user.sender;
        this.header.To = recipient;
        this.header.Subject = subject;

        // Body 설정
        this.body = content;

    }

    public void makeReaderAndWriter() throws Exception {
        // 2. Reader & Writer 생성 (명령을 보내고 응답코드를 받기 위해)
        inFromServer = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
        printWriter = new PrintWriter(this.socket.getOutputStream(), true);

        /*
        220 smtp.naver.com ESMTP 7XRX+EQDRnWVaYNeFW94Lg - nsmtp
        */
        line = inFromServer.readLine();
        System.out.println(line); // 220

        if (!line.startsWith("220"))
            throw new Exception("SMTP서버가 아닙니다");
    }

    // 3. EHLO
    public void Ehlo(String smtpServer) throws Exception {
        System.out.println();
        System.out.println("EHLO "+smtpServer);

        /*
        250-smtp.naver.com Pleased to meet you
        250-SIZE 20971520
        250-8BITMIME
        250-PIPELINING
        250-AUTH PLAIN LOGIN
        250 ENHANCEDSTATUSCODES
         */
        printWriter.println("EHLO "+smtpServer); // EHLO 명령어 전송
        line = inFromServer.readLine();
        System.out.println(line); // 250
        line = inFromServer.readLine();
        System.out.println(line); // 250
        line = inFromServer.readLine();
        System.out.println(line); // 250
        line = inFromServer.readLine();
        System.out.println(line); // 250
        line = inFromServer.readLine();
        System.out.println(line); // 250
        line = inFromServer.readLine();
        System.out.println(line); // 250
        if (!line.startsWith("250"))
            throw new Exception("서버 연결에 실패했습니다");
    }

    // 4 AUTH LOGIN
    public void authLogin(String username, String password) throws Exception {
        String encryptedUsername = Base64.getEncoder().encodeToString(username.getBytes(StandardCharsets.UTF_8));
        String encryptedPassword = Base64.getEncoder().encodeToString(password.getBytes(StandardCharsets.UTF_8));

        System.out.println();
        System.out.println("AUTH LOGIN");

        /*
        334 VXNlcm5hbWU6
        334 UGFzc3dvcmQ6
        235 2.7.0 Accepted Emhh66c9Rn26pkBARTBxqQ - nsmtp
         */
        printWriter.println("AUTH LOGIN "); // AUTH LOGIN 명령어 전송
        line = inFromServer.readLine();
        System.out.println(line); // 334
        printWriter.println(encryptedUsername); // ID 전송
        line = inFromServer.readLine();
        System.out.println(line); // 334
        printWriter.println(encryptedPassword); // PASSWORD 전송
        line = inFromServer.readLine();
        System.out.println(line); // 235
        if (!line.startsWith("235"))
            throw new Exception("로그인에 실패했습니다");
    }

    // 5. MAIL FROM
    public void MailFrom() throws Exception {
        System.out.println();
        System.out.println("MAIL FROM:<"+this.header.From+">");

        /*
        250 2.1.0 OK Emhh66c9Rn26pkBARTBxqQ - nsmtp
         */
        printWriter.println("MAIL FROM:<"+this.header.From+">"); // MAIL FROM 명령어 전송
        line = inFromServer.readLine();
        System.out.println(line); // 250
        if (!line.startsWith("250"))
            throw new Exception("보내는 이메일 입력값을 확인해주세요");
    }

    // 6. RCTP TO
    public void RctpTo() throws Exception {
        System.out.println();
        System.out.println("RCPT TO:<" + this.header.To + ">");

        /*
        250 2.1.5 OK Emhh66c9Rn26pkBARTBxqQ - nsmtp
         */
        printWriter.println("RCPT TO:<" + this.header.To + ">"); // RCPT TO 명령어 전송
        line = inFromServer.readLine(); 
        System.out.println(line); // 250
        if (!line.startsWith("250"))
            throw new Exception("받는 이메일 입력값을 확인해주세요");
    }

    // DATA 명령전송 -> 응답코드(354) 코드 확인 
    // 7. DATA
    public void data() throws Exception {
        System.out.println();
        System.out.println("DATA");

        /*
        354 Go ahead Emhh66c9Rn26pkBARTBxqQ - nsmtp
         */
        printWriter.println("DATA"); // DATA 명령어 전송
        line = inFromServer.readLine();
        System.out.println(line); // 354
        if (!line.startsWith("354"))
            throw new Exception("DATA 명령이 실패했습니다");
    }

    // 본문 & 파일(MIME)전송 -> . 전송 -> 응답코드(250) 확인
    // 8. SEND CONTENT
    public void sendMailContent(ArrayList<File> attachedFile) throws Exception {

        System.out.println();
        System.out.println("From: " + this.header.From);
        printWriter.println("From: " + this.header.From); // 보내는 사람 전송

        System.out.println("To: " + this.header.To);
        printWriter.println("To: " + this.header.To); // 받는 사람 전송

        System.out.println("Subject: " + this.header.Subject);
        printWriter.println("Subject: " + this.header.Subject); // 제목 전송

        // MIME 설정
        printWriter.println("MIME-Version: 1.0");
        printWriter.println("Content-Type: multipart/mixed; boundary=boundary_string");
        printWriter.println();
        printWriter.println("--boundary_string");

        // 본문
        if (!this.body.isEmpty()) {
            printWriter.println("Content-Type: text/plain; charset=UTF-8");
            printWriter.println();
            System.out.println(this.body);
            printWriter.println(this.body); // 본문 전송
            printWriter.println("--boundary_string");
        }
        
        // 파일
        if (attachedFile != null && !attachedFile.isEmpty()) {
            for(int i=0;i<attachedFile.size();i++){
                printWriter.println("--boundary_string");
                printWriter.println("Content-Type: application/octet-stream; name=\"" + attachedFile.get(i).getName() + "\"");
                printWriter.println("Content-Transfer-Encoding: base64");
                printWriter.println("Content-Disposition: attachment; filename=\"" + attachedFile.get(i).getName() + "\"");
                printWriter.println();

                FileInputStream fileInputStream = new FileInputStream(attachedFile.get(i));
                byte[] fileBytes = new byte[(int) attachedFile.get(i).length()];
                fileInputStream.read(fileBytes);
                fileInputStream.close();

                String encodedFile = Base64.getEncoder().encodeToString(fileBytes);
                printWriter.println(encodedFile); // 파일 전송
                printWriter.println("--boundary_string");

            }
        }

        printWriter.println("--boundary_string--");
        printWriter.println("."); // . 전송 (데이터 전송 종료를 의미)

        /*
        250 2.0.0 OK Emhh66c9Rn26pkBARTBxqQ - nsmtp
         */
        line = inFromServer.readLine();
        System.out.println(line); // 250
        if (!line.startsWith("250")) {
            throw new Exception("내용전송이 실패했습니다");
        }
    }

    // 9. QUIT
    public void quit() throws Exception {
       System.out.println();
        System.out.println("QUIT");

        /*
        221 2.0.0 Closing connection Emhh66c9Rn26pkBARTBxqQ - nsmtp
         */
        printWriter.println("QUIT");
        line = inFromServer.readLine();
        System.out.println(line); // 221
        if (!line.startsWith("221"))
            throw new Exception("서버와 연결이 종료되지 않았습니다.");
    }

    // 10. CLOSE
    public void close() throws IOException {
        printWriter.close();
        inFromServer.close();
        socket.close();
    }
}


/*
 * SMTPSender 클래스 : 메일 발송
 */
public class SMTPSender {

    public static void sendMail(User user, String recipient, String subject, String content, ArrayList<File> attachedFile) throws Exception {
        final String smtpServer = "smtp.naver.com";
        final int smtpServerPort = 465;

        try {
            // 1. 소켓 생성
            SocketMaker socket = new SocketMaker(smtpServer, smtpServerPort, user, recipient, subject, content);

            // 2. BufferReader PrintWriter 생성
            socket.makeReaderAndWriter();

            // 3. EHLO
            socket.Ehlo(smtpServer);

            // 4. AUTH LOGIN
            socket.authLogin(user.username, user.password);

            // 5. MAIL FROM
            socket.MailFrom();

            // 6. RCPT TO
            socket.RctpTo();

            // 7. DATA
            socket.data();

            // 8. content 및 파일 첨부
            socket.sendMailContent(attachedFile);

            // 9. QUIT
            socket.quit();

            // 10. socket close
            socket.close();
            
        } catch (Exception exception) {
            throw exception;
        }

    }

    public static void main(String[] args) throws Exception {
        try {
            new Login();
        } catch (Exception e) {
            System.out.println("==========================");
            System.out.println("메일이 발송되지 않았습니다.");
            System.out.println(e.toString());
        }
    }
}