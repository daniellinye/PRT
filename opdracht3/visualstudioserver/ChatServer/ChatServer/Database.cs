using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;
using System.Data.SqlTypes;


namespace ChatServer
{
    class Database
    {

    }


    class DatabaseFunctions
    {
        public DatabaseFunctions()
        {

        }

        //executes a function on the database and returns values
        public string ExecuteFunction(string function, string args)
        {
            //TODO:
            //add basic functionalities to login, getmessages
            //sendmessages, getuser, sendmessages and login
            switch (function)
            {
                default:
                    Console.WriteLine("DatabaseFunction: " + function + " not recognized or implemented.");
                    break;
            }

            return null;
        }

        public void LogIn(string username, string password)
        {

            try
            {
                //Is now hardcoded but should be an online service
                //service is not available yet, so this is hardcoded
                //for testing: change the Path after AttachDbFilename=
                using (SqlConnection connection = new SqlConnection("Data Source=(LocalDB)\\MSSQLLocalDB;AttachDbFilename=D:\\Studie\\PRT\\opdracht3\\visualstudioserver\\ChatServer\\ChatServer\\users.mdf;Integrated Security=True"))
                {
                    Console.WriteLine("Opening connection");
                    connection.Open();
                    Executecommand(connection, "DELETE FROM users");
                    Executecommand(connection, "INSERT INTO users (name,password) VALUES ('" + username + "','" + password + "')");

                    SqlDataReader reader = GetTables(connection, "SELECT * FROM users");

                    while (reader.Read())
                    {
                        Console.WriteLine(reader["name"].ToString());
                    }
                }
                Console.WriteLine("Connection Successful");
            }
            catch
            {
                Console.WriteLine("Connection Unsuccesfull");
            }

        }

        public void Executecommand(SqlConnection dbconnection, string query)
        {
            try
            {
                SqlCommand sqlcommand = new SqlCommand(query, dbconnection);
                sqlcommand.ExecuteNonQuery();
            }
            catch
            {
                Console.WriteLine(query);
            }
        }


        public SqlDataReader GetTables(SqlConnection dbconnection, string query)
        {
            SqlCommand sqlcommand = new SqlCommand();
            sqlcommand.CommandText = query;
            sqlcommand.Connection = dbconnection;

            return sqlcommand.ExecuteReader();
        }
    }

}
