using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using System.Text;
using System.Threading.Tasks;


public class Serial_Test : MonoBehaviour
{
    SerialPort sp = new SerialPort("COM3", 115200, Parity.None, 8, StopBits.None);     //시리얼 포트 열어주기
    public static byte[] parsing_send_data = new byte[8];
    public static int recv_num = 0;


    void Start()                            // 시작시 1 번 실행
    {

        sp.Open();              //포트 열어줌
        sp.ReadTimeout = 100;

        foreach (string str in SerialPort.GetPortNames())
        {
            Debug.Log(string.Format("Existing COM port: {0}", str));
        }
    }



    // Update is called once per frame
    void Update()
    {
        sp_Check();


        if (Input.GetKeyDown(KeyCode.A))
        {
            Debug.Log("A");
            parsing_send_data[0] = 65;// A
            sp.Write(parsing_send_data, 0, 1);
            //Debug.LogError("A");
        }

    }


    public void sp_Check()
    {
        if (sp.IsOpen)          //포트 열리면
        {
            try
            {

            }
            catch (System.Exception e)
            {
                print(e);
                sp.Close();
                throw;

            }
        }
    }
}
