import java.awt.*;
import javax.swing.*;

public class Login extends JFrame {
    private JTextField ID = new JTextField(30);
    private JPasswordField Password = new JPasswordField(30);

    public Login() {

        // 타이틀 설정
        setTitle("네이버 메일");
        JPanel title = new JPanel();

        // 아이콘 이미지 설정
        ImageIcon icon = new ImageIcon("img\\navermail.png");
        setIconImage(icon.getImage()); 

        // 로그인 입력창
        JPanel jp1 = new JPanel();
        jp1.setLayout(new GridLayout(3, 2));


        // ID 입력 
        JPanel idPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        JLabel jlb1 = new JLabel("아이디 : ", JLabel.CENTER);
        jlb1.setFont(new Font("Dialog", Font.PLAIN, 15));
        idPanel.add(jlb1);
        
        JPanel idPanel2 = new JPanel(new FlowLayout(FlowLayout.LEFT));
        JTextField IDField = new JTextField(10);
        IDField.add(ID);
        idPanel2.add(IDField);

        jp1.add(idPanel);
        jp1.add(idPanel2);

        // 비밀번호 입력
        JPanel pwdPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        JLabel jlb2 = new JLabel("비밀번호 : ", JLabel.CENTER);
        jlb2.setFont(new Font("Dialog", Font.PLAIN, 15));
        pwdPanel.add(jlb2);
        
        JPanel pwdPanel2 = new JPanel(new FlowLayout(FlowLayout.LEFT));
        JPasswordField PasswordField = new JPasswordField(10);
        PasswordField.add(Password);
        pwdPanel2.add(PasswordField);

        jp1.add(pwdPanel);
        jp1.add(pwdPanel2);


        // 다음(로그인) 버튼
        JPanel loginPanel = new JPanel(new BorderLayout());
        JButton jLogin = new JButton("다음");
        loginPanel.add(jLogin);
        
        JPanel jp3 = new JPanel();
        jp3.add(loginPanel);

        JPanel jp2 = new JPanel();
        jp2.setLayout(new FlowLayout());
        jp2.add(jp1);

        // 전체 패널 설정
        setLayout(new BorderLayout());
        add(title, BorderLayout.NORTH);
        add(jp2, BorderLayout.CENTER);
        add(jp3, BorderLayout.SOUTH);

        setBounds(300, 300, 300, 150);

        Dimension frameSize = getSize();
        Dimension windowSize = Toolkit.getDefaultToolkit().getScreenSize();
        setLocation((windowSize.width - frameSize.width) / 2, (windowSize.height - frameSize.height) / 2);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setVisible(true);

        // 다음(로그인) 버튼 이벤트 처리
        jLogin.addActionListener(e -> {
            String id = IDField.getText();
            String password = new String(PasswordField.getPassword());
            String naverMail = "@naver.com";
            String sender = id + naverMail;
            User user = new User(id, password, sender);

            if (id.isEmpty()) {
                JOptionPane.showMessageDialog(null, "ID를 입력하세요", "오류", JOptionPane.ERROR_MESSAGE);
            } else if (password.isEmpty()) {
                JOptionPane.showMessageDialog(null, "비밀번호를 입력하세요", "오류", JOptionPane.ERROR_MESSAGE);
            } else {
                new MailSend(user);
                dispose();
            }
        });
    }
}
