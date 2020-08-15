
```C#
using Microsoft.VisualBasic.CompilerServices;
using System;
using System.Runtime.InteropServices;
using System.Text;

namespace dllcalltest
{
    static class CWrapper
    {
        // 構造体への参照渡しにはclassを使う。属性の設定は必須。
        [StructLayout(LayoutKind.Sequential)]
        public class MyPos
        {
            public int x;
            public int y;
        }
        [DllImport("Dll164.dll", EntryPoint ="Test1")]
        public static extern void Test1();
        [DllImport("Dll164.dll", EntryPoint = "add")]
        public static extern int add(int a, int b);
        [DllImport("Dll164.dll", EntryPoint = "mystrcpy")]
        public static extern void mystrcpy(StringBuilder dest, string src);
        [DllImport("Dll164.dll", EntryPoint = "add_array")]
        public static extern void add_array(int num, IntPtr src1, IntPtr src2, IntPtr dest);
        [DllImport("Dll164.dll", EntryPoint = "movepos")]
        public static extern void movepos([In][Out]MyPos pos);
        [DllImport("Dll264.dll", EntryPoint = "Test2")]
        public static extern void Test2();
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            CWrapper.Test1();
            CWrapper.Test2();
            var val = CWrapper.add(3, 5);
            Console.WriteLine("add() = " + Convert.ToString(val));

            StringBuilder dest = new StringBuilder(1024);
            string src = "this is a text.";
            CWrapper.mystrcpy(dest, src);
            Console.WriteLine(dest.ToString());

            int[] arr1 = { 1, 2, 3, 4 };
            int[] arr2 = { 5, 6, 7, 8 };
            int size = Marshal.SizeOf(arr1[0]) * arr1.Length;
            IntPtr src1 = Marshal.AllocHGlobal(size);
            IntPtr src2 = Marshal.AllocHGlobal(size);
            IntPtr dest2 = Marshal.AllocHGlobal(size);
            try
            {
                Marshal.Copy(arr1, 0, src1, arr1.Length);
                Marshal.Copy(arr2, 0, src2, arr2.Length);
                CWrapper.add_array(arr1.Length, src1, src2, dest2);
                int[] arr3 = new int[arr1.Length];
                Marshal.Copy(dest2, arr3, 0, arr1.Length);
                for ( int i = 0; i < arr1.Length; i++ )
                {
                    var tmp = String.Format("{0} + {1} = {2}", arr1[i], arr2[i], arr3[i]);
                    Console.WriteLine(tmp);
                }
            }
            finally
            {
                Marshal.FreeHGlobal(src1);
                Marshal.FreeHGlobal(src2);
                Marshal.FreeHGlobal(dest2);
            }
            var pos = new CWrapper.MyPos();
            pos.x = 100;
            pos.y = 300;
            CWrapper.movepos(pos);
            Console.WriteLine(String.Format("x = {0}, y = {1}", pos.x, pos.y));
        }
    }
}

```
