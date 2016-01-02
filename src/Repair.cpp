/**
 * Repair
 * This executable is responsible for validating and fixing all paths and files.
 * It needs to be run as an administrator (Windows), or as root (Linux), or as a user (Linux/Mac) 
 * with permsissions to write the app directory and the shared directory.
 * 
 * Arguments the Repair binary can filter it down to doing only certain tasks.
 */
int main (int argc, char** argv)
{
	Backend::Application app;
	return app.Exec();
}