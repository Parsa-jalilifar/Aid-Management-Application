#ifndef AID_ERROR_H
#define AID_ERROR_H


namespace aid{

	class Error
	{
		char* m_Message;

	public:

		explicit Error(const char* errorMessage = nullptr);
		void clear();
		bool isClear() const;
		void message(const char* str); 
		const char* message() const;
		
		Error(const Error& error) = delete;
		Error& operator=(const Error& error) = delete;
		virtual ~Error();
	
	};

	std::ostream& operator<<(std::ostream& os, const Error& error);

}
#endif 