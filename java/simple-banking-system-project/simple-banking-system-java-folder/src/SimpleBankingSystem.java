import javax.swing.*;
import java.io.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.time.*;

class Account{
	String accountNum;
	String passwordNum;
	int balance;
	
	public Account(String acc, String pw){
		this.accountNum = acc;
		this.passwordNum = pw;
		this.balance = -1;
		// 초기 음수로 설정하여 가장 최신 잔액을 불러올 수 있도록 잔액 초기화
	}
} // Account 배열을 위한 객체 생성

class Login extends JFrame{ // 로그인 프레임 
	private JTextField account = new JTextField(20);
	private JTextField password = new JTextField(20);
	static Account[] ac = new Account[3];
	
	public Login() throws IOException {
		setLocationRelativeTo(null); 
		setTitle("Login"); 
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(new FlowLayout());
		JButton next = new JButton("Next");

		c.add(new JLabel("Account "));
		c.add(account);
		c.add(new JLabel("Password "));
		c.add(password);
		c.add(next,"Center"); // 계좌번호, 비밀번호 입력을 위한 JLabel, JBotton
	
		// 파일 읽어들여 Account 객체로 초기화
		int i=0;
		try {
			FileReader Data= new FileReader("c:\\temp\\bankaccount.txt"); 
			BufferedReader bufReaderD = new BufferedReader(Data);
			String[] token;
			String line = "";
			while ((line = bufReaderD.readLine())!=null) {
				token = line.split(" ");
				if (token.length < 2) {
					continue;
				}
				ac[i] = new Account(token[0], token[1]);
				i++;
			}
			// 은행 계좌&비밀번호 저장
			FileReader History = new FileReader("c:\\temp\\transactions.txt");
			BufferedReader bufReaderH = new BufferedReader(History);
			line = "";
			while((line = bufReaderH.readLine())!=null) {
				token = line.split(" ");
				if (token.length < 2) {
					continue;
				}
				for (int j=0; j<3; j++) {
					if (ac[j].accountNum.equals(token[0])) {
						if (ac[j].balance < 0) {
							ac[j].balance = Integer.parseInt(token[1]);
						}
					}
				}
			}
			// 계좌 내역 마지막 잔액 저장
			bufReaderH.close();
		} 
		catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} // 파일 읽기 예외처리
	
		next.addActionListener(new ActionListener() { // 버튼이 눌러졌을 경우의 액션리스터
			@Override
			public void actionPerformed(ActionEvent e) {
				int tmp=0;
				for (int i=0; i<3; i++) {
					if (ac[i].accountNum.equals(account.getText())
							&& ac[i].passwordNum.equals(password.getText())) {
							// 로그인을 성공했을 경우
						tmp = 1;
						new Command(ac[i]); // *커맨드 창 띄우기  
						setVisible(false); // 창 안보이게 하기 
					}
				}
				if (tmp == 0) { // 로그인을 실패하였을 경우 (매치되는 계좌번호와 비밀번호를 찾지 못하였을 경우)
					JOptionPane.showMessageDialog(null, "※ Login failed ※\nPlease re-enter");
					// *오류 메시지 출력
					try {
						new Login(); // *재입력을 위해 로그인 창 띄우기
				} 
				catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
    			setVisible(false);
			}
        }
    });
	c.add(next);
	setSize(250,200);
	setVisible(true);
	}
	
}

class Command extends JFrame{ // 명령어 3가지를 선택할 수 있는 JFrame
	public Command(Account A) {
		setLocationRelativeTo(null); 
		setTitle("Command"); // 타이틀
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(new FlowLayout());
		JButton balanceBtn = new JButton("Balance");
		JButton withdrawBtn  = new JButton("Withdraw");
		JButton depositBtn  = new JButton("Deposit");
		
		c.add(balanceBtn);
		c.add(withdrawBtn);
		c.add(depositBtn);
		// *로그인 후의 3가지 기능 선택을 위한 버튼
		
		balanceBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	new Balance(A); // 잔액을 선택하였을 경우 잔액 창 띄우기
                setVisible(false); // 창 안보이게 하기 
            }
        });
		
		withdrawBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	new Withdraw(A); // 출금을 선택하였을 경우 출금 창 띄우기
                setVisible(false); // 창 안보이게 하기 
            }
        });
		
		depositBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	new Deposit(A); // 입금을 선택하였을 경우 입금 창 띄우기
                setVisible(false); // 창 안보이게 하기 
            }
        });
		setSize(300,100);
		setVisible(true);
	}
}

class Balance extends JFrame{ // 잔액을 확인해주는 JFrame
	private JLabel balance = new JLabel();
	public Balance(Account A) {
		setLocationRelativeTo(null); 
		setTitle("Balance"); // 타이틀
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(new FlowLayout());
		
    	JOptionPane.showMessageDialog(null, "Account's balance is " + A.balance +"won");
    	// *현재 계좌의 잔액을 출력
		
    	new SimpleBankingSystem(); // 잔액 표시 완료 후 초기화면으로
		setVisible(false);	
		}
}

class Withdraw extends JFrame{ // 출금을 진행하는 JFrame
	private JTextField password = new JTextField(20);
	String amount="";
	int PWC = 0;
	public Withdraw(Account A) {
		setLocationRelativeTo(null); 
		setTitle("Withdraw"); // 타이틀
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(new FlowLayout());
		JButton passwordBtn = new JButton("Next");
		
		c.add(new JLabel("Password Confirmation "));
		c.add(password);
		c.add(passwordBtn);
		// * 비밀번호를 다시한번 요청하여 입력받기 (버튼을 통해 확인함)
		
		passwordBtn.addActionListener(new ActionListener() {
			 @Override
			public void actionPerformed(ActionEvent e) {
	           	if (A.passwordNum.equals(password.getText())) {
	           		// *비밀번호 확인 후 일치한다면
	           		amount = JOptionPane.showInputDialog("Enter the amount to withdraw");
	           		// *출금액 입력받기
	           		if (Integer.parseInt(amount) > A.balance) {
	           			// 잔액이 부족할 경우
	           			JOptionPane.showMessageDialog(null, "※ Lack of Balance ※");
	           			// *잔액이 부족하다는 오류메시지 출력
	                	new Command(A); // *로그인 직후 화면으로
	    	            setVisible(false);
	            	}
	           		else {
	           			try {
	               			Thread.sleep(3000);
	               		}
	              		catch(InterruptedException e1) {
	              			return;
	            		} // 3초가 지난 후 (출금 과정을 생각하여 추가)
	           			A.balance -= Integer.parseInt(amount); // 잔액에 반영
	           			LocalDate now = LocalDate.now(); // 내역 파일에 삽입하기 위한 날짜 파악
	           			try {
	           				String line="";
	           				File f = new File("c:\\temp\\transactions.txt");
	            			try (BufferedReader bufReader = new BufferedReader(new FileReader(f))) {
								String Text = A.accountNum+" "+A.balance+" " + now + " withdraw " + amount + "\r\n";
								while((line = bufReader.readLine())!=null) {
									Text += (line + "\r\n");
								}
								BufferedWriter buffWrite = new BufferedWriter(new FileWriter(f));
								buffWrite.write(Text, 0, Text.length());
								buffWrite.flush();
								buffWrite.close();
							}
	            	    	JOptionPane.showMessageDialog(null, amount + "won withdral completed");
	            	    	// 출금 성공 메시지 출력
	           			} catch (IOException e1) {
	           				// TODO Auto-generated catch block
	           				e1.printStackTrace();
	           			}
	           			// *해당 내용을 거래 내역 파일에 삽입
	           			new SimpleBankingSystem();
	           			setVisible(false); // 출금완료 후 초기화면으로
	           		}	
	            }
	           	else {
            		JOptionPane.showMessageDialog(null, "※ Password Mismatch ※");
	           		// 비밀번호 불일치 오류 메시지 출력
           			new SimpleBankingSystem();
           			setVisible(false); // 비밀번호 불일치시 초기화면으로
	            }
			}
		});
		setSize(500,150);
		setVisible(true);
	}
}

class Deposit extends JFrame{ // 입금을 진행하는 JFrame
	String amount="";
	public Deposit(Account A) {
		setLocationRelativeTo(null); 
		setTitle("Deposit"); // 타이틀
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(new FlowLayout());
		
		amount = JOptionPane.showInputDialog("Insert Cash");
		// *사용자에게 현금을 넣으라는 안내메시지 출력 & 금액 입력받기
		
        A.balance += Integer.parseInt(amount);
        // 잔액에 반영
		try {
			Thread.sleep(3000); 
		}
		catch(InterruptedException e1) {
			return;
		} // *3초가 지난 후
    	JOptionPane.showMessageDialog(null, amount + "won deposit completed");
    	// 입금 성공 메시지 출력
		LocalDate now = LocalDate.now(); // 내역 파일에 삽입하기 위한 날짜 파악
		try {
			String line="";
			File f = new File("c:\\temp\\transactions.txt");
			try (BufferedReader bufReader = new BufferedReader(new FileReader(f))) {
				String Text = A.accountNum+" "+A.balance+" "+ now + " deposit " + amount + "\r\n";						
			while((line = bufReader.readLine())!=null) {
					Text += (line + "\r\n");
				}
				BufferedWriter buffWrite = new BufferedWriter(new FileWriter(f));
				buffWrite.write(Text, 0, Text.length());
				buffWrite.flush();
				buffWrite.close();
			}
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} 
		// *해당 내용을 거래 내역 파일에 삽입

		new SimpleBankingSystem();
		setVisible(false); // 입금 완료 후 초기화면으로
	}
}

class Simulation extends JFrame{ // 시뮬레이션을 진행하는 JFrame
	JLabel Loading = new JLabel();
	public Simulation() throws IOException {
		 setLocationRelativeTo(null); 
		 setTitle("--- Simulation in Progress ---"); // 타이틀
		 setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		 Container c = getContentPane();
		 c.setLayout(new FlowLayout());
		 // 시뮬레이션중임을 알리는 메시지 출력 (3초 대기 명령이 존재하기 때문)
		 setSize(350,50);
		 setVisible(true);
		 
		 SimulationThread.simulation();
		 
	     JOptionPane.showMessageDialog(null, "--- Simulation Ended Successfully ---");
		 
 		 new SimpleBankingSystem();
 		 setVisible(false); // 시뮬레이션 진행 후 초기화면으로
	}
}

class SimulationThread extends Thread{ // *시뮬레이션 스레드
	public static void simulation() throws IOException {
		Account[] ac = new Account[3];
		int i=0;
		try {
			FileReader Data= new FileReader("c:\\temp\\bankaccount.txt");
			BufferedReader bufReaderD = new BufferedReader(Data);
			String[] token;
			String line = "";
			while ((line = bufReaderD.readLine())!=null) {
				token = line.split(" ");
				if (token.length < 2) {
					continue;
				}
				ac[i] = new Account(token[0], token[1]);
				i++;
			}
			// 은행 계좌&비밀번호 저장
			FileReader History = new FileReader("c:\\temp\\transactions.txt");
			BufferedReader bufReaderH = new BufferedReader(History);
			line = "";
			while((line = bufReaderH.readLine())!=null) {
				token = line.split(" ");
				if (token.length < 2) {
					continue;
				}
				for (int j=0; j<3; j++) {
					if (ac[j].accountNum.equals(token[0])) {
						if (ac[j].balance < 0) {
							ac[j].balance = Integer.parseInt(token[1]);
						}
					}
				}
			}
			// 계좌 잔액 저장
			bufReaderH.close();
		} 
		catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} // 파일 읽어들이기 성공
		
		//
		int tmp=0;
		try {
			FileReader Data= new FileReader("c:\\temp\\simulation.txt");
			BufferedReader bufReader = new BufferedReader(Data);
			String[] token_;
			String line = "";
			while ((line = bufReader.readLine())!=null) {
				tmp = 0;
				token_ = line.split(" ");
				if (token_.length < 3) {
					continue;
				}
				for (int j=0; j<3; j++) {
					if (ac[j].accountNum.equals(token_[0]) && ac[j].passwordNum.equals(token_[1])) {
						tmp = 1; // 로그인 성공
						if (token_[2].equals("withdraw")) {
							if (Integer.parseInt(token_[3]) > ac[j].balance) {
		            			JOptionPane.showMessageDialog(null, "※ Lack of Balance ※");
		            		}
		            		else {
		            			try {
		                			Thread.sleep(3000); // 3초동안 잠을 잔다.
		                		}
		               			catch(InterruptedException e1) {
		               				return; // 예외가 발생하면 스레드 종료
		               			}
		            			ac[j].balance -= Integer.parseInt(token_[3]);
		            			LocalDate now = LocalDate.now();
		            			try {
		            				String line_ = "";
		            				File f = new File("c:\\temp\\transactions.txt");
		            				try (BufferedReader bufReader1 = new BufferedReader(new FileReader(f))) {
										String Text = ac[j].accountNum+" "+ac[j].balance+" " + now + " withdraw " + token_[3] + "\r\n";
										while((line_ = bufReader1.readLine())!=null) {
											Text += (line_ + "\r\n");
										}
										BufferedWriter buffWrite = new BufferedWriter(new FileWriter(f));
										buffWrite.write(Text, 0, Text.length());
										buffWrite.flush();
										buffWrite.close();
									}
		            		    	JOptionPane.showMessageDialog(null, token_[3] + "won withdral completed");
		            			} catch (IOException e1) {
		            				// TODO Auto-generated catch block
		            				e1.printStackTrace();
		            			}
		            		}
						}
						else if (token_[2].equals("deposit")) {
					        ac[j].balance += Integer.parseInt(token_[3]);
							try {
								Thread.sleep(3000); 
							}// 3초동안 잠을 잔다.	
							catch(InterruptedException e1) {
								return; // 예외가 발생하면 스레드 종료
							}
					    	JOptionPane.showMessageDialog(null, token_[3] + "won deposit completed");
							LocalDate now = LocalDate.now();
							try {
								String line__="";
								File f = new File("c:\\temp\\transactions.txt");
								try (BufferedReader bufReader1 = new BufferedReader(new FileReader(f))) {
									String Text = ac[j].accountNum+" "+ac[j].balance+" "+ now + " deposit " + token_[3] + "\r\n";						
								while((line__ = bufReader1.readLine())!=null) {
										Text += (line__ + "\r\n");
									}
									BufferedWriter buffWrite = new BufferedWriter(new FileWriter(f));
									buffWrite.write(Text, 0, Text.length());
									buffWrite.flush();
									buffWrite.close();
								}
							} catch (IOException e1) {
								// TODO Auto-generated catch block
								e1.printStackTrace();
							}
						}
						else if (token_[2].equals("balance")) {
					    	JOptionPane.showMessageDialog(null, "Account's balance is " + ac[j].balance +"won");
						}
					}
				}
				if (tmp == 0) {
	    			JOptionPane.showMessageDialog(null, "※ Login failed ※\nPlease re-enter");
				}
			}
		} 
		catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} // 파일 읽어들이기 성공
	}
}

public class SimpleBankingSystem extends JFrame {
	public SimpleBankingSystem() { // 초기화면
		 setLocationRelativeTo(null); 
		setTitle("seom-j's simple-banking-system"); // 타이틀
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Container c = getContentPane();
		c.setLayout(new FlowLayout());

		JButton loginBtn = new JButton("Login");
		JButton simulationBtn = new JButton("Simulation");

		c.add(loginBtn);
		c.add(simulationBtn); // *최초 구동 화면 버튼 구현
		setSize(350,100);
		setVisible(true);
		
		loginBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
					new Login();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
                setVisible(false); // 창 안보이게 하기 
            }
        }); // 로그인 창으로 넘어가기
		
		simulationBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
					new Simulation();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
                setVisible(false); // 창 안보이게 하기 
            }
        }); // 시물레이션 창으로 넘어가기
	}
	
	public static void main(String[] args) throws IOException {
		new SimpleBankingSystem();
	}
}