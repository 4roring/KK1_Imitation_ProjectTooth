using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using Microsoft.DirectX.PrivateImplementationDetails;

namespace Tool
{
    internal class CDevice : CSingleton<CDevice>
    {
        private CDevice() { }

        private static CDevice _instance;

        public static CDevice Instance
        {
            get
            {
                if (_instance == null)
                    Application.Run(new CDevice());

                return _instance;
            }
        }

        private Device m_Device = null;
        private Sprite m_Sprite = null;

        public Device _Device
        {
            get { return m_Device; }
        }

        public Sprite Sprite
        {
            get { return m_Sprite; }
        }

        public void InitDevice()
        {
            PresentParameters presentParams = new PresentParameters();
            SetParameters(presentParams);
            m_Device = new Device(0, DeviceType.Hardware, this
                , CreateFlags.SoftwareVertexProcessing, presentParams);

            m_Sprite = new Sprite(m_Device);
        }

        private void SetParameters(PresentParameters presentParams)
        {
            presentParams.BackBufferWidth = Value.WINCX;
            presentParams.BackBufferHeight = Value.WINCY;
            presentParams.BackBufferFormat = Format.A8B8G8R8;
            presentParams.BackBufferCount = 1;
                      
            presentParams.MultiSample = MultiSampleType.None;
            presentParams.MultiSampleQuality = 0;
                       
            presentParams.SwapEffect = SwapEffect.Discard;
            presentParams.DeviceWindow = MainForm.ActiveForm;
            presentParams.Windowed = true;
                      
            presentParams.EnableAutoDepthStencil = true;
            presentParams.AutoDepthStencilFormat = DepthFormat.D24S8;
                   
            presentParams.FullScreenRefreshRateInHz = 0x00000000;
            presentParams.PresentationInterval = PresentInterval.Immediate;
        }

        public void RenderBegin()
        {
            m_Device.Clear(ClearFlags.Target, Color.Blue, 1.0f, 0);
            m_Device.BeginScene();
            m_Sprite.Begin(SpriteFlags.AlphaBlend);
        }

        public void RenderEnd()
        {
            m_Sprite.End();
            m_Device.EndScene();
            m_Device.Present(MainForm.ActiveForm);
        }
    }
}
