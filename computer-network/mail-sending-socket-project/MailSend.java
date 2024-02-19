import java.awt.*;
import java.io.File;
import java.util.ArrayList;
import javax.swing.*;

public class MailSend extends JFrame {
    JTextField sender = new JTextField(20);
    JTextField recipient = new JTextField(20);
    JTextField filename = new JTextField(30);
    JTextField subject = new JTextField(30);
    JTextArea content = new JTextArea(20, 30);
    JButton attachButton = new JButton("파일 첨부");
    JButton deleteFileButton = new JButton("파일 삭제");
    JButton addFielButton = new JButton("파일 추가");
    ArrayList<File> attachedFile = new ArrayList<File>();
    User user;

    public MailSend(User user) {

        // 타이틀 설정
        super("네이버 메일");
        this.user = user;

        // 아이콘 이미지 설정
        ImageIcon icon = new ImageIcon("img\\navermail.png"); 
        setIconImage(icon.getImage());

        /*
         * inputPanel 설정
         */
        JPanel inputPanel = new JPanel(new BorderLayout(10, 10));
        JPanel labelPanel = new JPanel(new GridLayout(7, 1, 5, 10));
        JPanel textFieldPanel = new JPanel(new GridLayout(7, 1, 5, 10));
        inputPanel.add(labelPanel, BorderLayout.WEST);
        inputPanel.add(textFieldPanel, BorderLayout.CENTER);


        /*
         * inputPanel / BorderLayout.WEST : 라벨 생성, 추가
         */
        // 라벨 생성
        JLabel senderLabel = new JLabel("보내는 이 :");
        senderLabel.setFont(new Font("Dialog", Font.PLAIN, 15));
        senderLabel.setBorder(BorderFactory.createEmptyBorder(10, 10, 0, 0));
        JLabel recipientLabel = new JLabel("받는 이 :");
        recipientLabel.setFont(new Font("Dialog", Font.PLAIN, 15));
        recipientLabel.setBorder(BorderFactory.createEmptyBorder(10, 10, 0, 0));
        JLabel sendToMeLabel = new JLabel("내게 쓰기");
        sendToMeLabel.setFont(new Font("Dialog", Font.PLAIN, 15));
        sendToMeLabel.setBorder(BorderFactory.createEmptyBorder(10, 10, 0, 0));
        JLabel attachLabel = new JLabel("파일 첨부 :"); 
        attachLabel.setFont(new Font("Dialog", Font.PLAIN, 15));
        attachLabel.setBorder(BorderFactory.createEmptyBorder(10, 10, 0, 0));
        JLabel filenameLabel = new JLabel("파일명 :");
        filenameLabel.setFont(new Font("Dialog", Font.PLAIN, 15));
        filenameLabel.setBorder(BorderFactory.createEmptyBorder(10, 10, 0, 0));
        JLabel subjectLabel = new JLabel("제목 :");
        subjectLabel.setFont(new Font("Dialog", Font.PLAIN, 15));
        subjectLabel.setBorder(BorderFactory.createEmptyBorder(10, 10, 0, 0));
        JLabel contentLabel = new JLabel("내용 :");
        contentLabel.setFont(new Font("Dialog", Font.PLAIN, 15));
        contentLabel.setBorder(BorderFactory.createEmptyBorder(10, 10, 0, 0));

        // 라벨 추가
        labelPanel.add(senderLabel);
        labelPanel.add(recipientLabel);
        labelPanel.add(sendToMeLabel);
        labelPanel.add(attachLabel);
        labelPanel.add(filenameLabel);
        labelPanel.add(subjectLabel);
        labelPanel.add(contentLabel);


        /*
         *  inputPanel / BorderLayout.CENTER : 텍스트 필드 생성, 추가 (버튼 포함)
         */
        // 텍스트 필드 생성
        // sender : 앞서 입력한 id (보내는 메일 주소 고정)
        sender.setText(this.user.sender);
        sender.setEditable(false);
        // 내게 쓰기 (체크 시 받는 메일 주소 고정)
        JCheckBox sendToMe = new JCheckBox();
        sendToMe.addActionListener(e -> {
            if (sendToMe.isSelected()) {
                recipient.setText(sender.getText());
                recipient.setEditable(false);
            } else {
                recipient.setText("");
                recipient.setEditable(true);
            }
        });
        // filename filed (수정 불가)
        filename.setEditable(false);
        // 파일 첨부 버튼 이벤트 처리
        attachButton.addActionListener(e -> {
            JFileChooser fileChooser = new JFileChooser();
            int result = fileChooser.showOpenDialog(this);
            if (result == JFileChooser.APPROVE_OPTION) {
                File selectedFile = fileChooser.getSelectedFile();
                attachedFile.add(selectedFile);
                filename.setText(attachedFile.stream()
                        .map(File::getName)
                        .reduce((f1, f2) -> f1 + ", " + f2)
                        .orElse(""));
                JOptionPane.showMessageDialog(null, "파일이 첨부되었습니다.", "파일 첨부 성공", JOptionPane.INFORMATION_MESSAGE);
            }
        });
        // 파일 삭제 버튼 이벤트 처리
        deleteFileButton.addActionListener(e -> {
            if (attachedFile.isEmpty()) {
                JOptionPane.showMessageDialog(null, "첨부된 파일이 없습니다.", "파일 삭제 실패", JOptionPane.WARNING_MESSAGE);
            } else {
                attachedFile.clear();
                filename.setText("");
                JOptionPane.showMessageDialog(null, "첨부된 파일이 삭제되었습니다.", "파일 삭제 성공", JOptionPane.INFORMATION_MESSAGE);
            }
        });
        // 파일 패널 생성
        JPanel filePanel = new JPanel(new BorderLayout());
        filePanel.add(filename, BorderLayout.CENTER);
        filePanel.add(deleteFileButton, BorderLayout.EAST);

        // 텍스트 필드 추가
        textFieldPanel.add(sender);
        textFieldPanel.add(recipient);
        textFieldPanel.add(sendToMe);
        textFieldPanel.add(attachButton);
        textFieldPanel.add(filePanel);
        textFieldPanel.add(subject);
        textFieldPanel.setBorder(BorderFactory.createEmptyBorder(10, 0, 0, 10));
        content.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        content.setLineWrap(true);
        content.setWrapStyleWord(true);
        JScrollPane contentScrollPane = new JScrollPane(content);
        contentScrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS); // 스크롤바 항상 표시


        /*
         * buttonPanel 설정
         */
        JButton back = new JButton("이전");
        JButton send = new JButton("전송");
        JButton exit = new JButton("닫기");
        // 이전 버튼 이벤트 처리
        back.addActionListener(e -> {
            new Login();
            dispose();
        });
        // 전송 버튼 이벤트 처리
        send.addActionListener(e -> {
            if (e.getSource() == send) {
                try {
                    SMTPSender.sendMail(
                            this.user,
                            recipient.getText(),
                            subject.getText(),
                            content.getText(),
                            attachedFile);
                    JOptionPane.showMessageDialog(null, "메일을 전송하였습니다.", "전송 성공", JOptionPane.INFORMATION_MESSAGE);
                } catch (Exception ex) {
                    JOptionPane.showMessageDialog(
                            null, "메일전송이 실패하였습니다.\n " + ex.getMessage(), "전송 실패", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        // 닫기 버튼 이벤트 처리
        exit.addActionListener(e -> {
            if (e.getSource() == exit) {
                System.exit(0);
            }
        });
        // 버튼 패널 생성 & 추가
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(back);
        buttonPanel.add(send);
        buttonPanel.add(exit);

        /*
         * 전체 패널 설정
         */
        this.setSize(500, 600);
        this.add(inputPanel, BorderLayout.NORTH);
        this.add(contentScrollPane, BorderLayout.CENTER);
        this.add(buttonPanel, BorderLayout.SOUTH);
        Dimension frameSize = getSize();
        Dimension windowSize = Toolkit.getDefaultToolkit().getScreenSize();
        setLocation((windowSize.width - frameSize.width) / 2,
                (windowSize.height - frameSize.height) / 2);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setVisible(true);
    }
}