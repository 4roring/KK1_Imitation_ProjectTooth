using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tool
{
    public class CSingleton<T> where T : class, new()
    {
        private static object m_Lock = new object();
        private static volatile T m_Instance = null;

        protected CSingleton() { }

        public static T GetInstance
        {
            get
            {
                lock(m_Lock)
                {
                    if (m_Instance == null)
                        m_Instance = new T();
                }
               
                return m_Instance;
            }
        }     
    }
}