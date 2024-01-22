Program Assistant
usage 

pass
	=> with no arguments will open pass in interactive mode.
	=> in interactive mode, you can ommit keeping 'pass' at the beginning of every command

pass /?
pass help
	-- opens help for the program assistant

pass open <program name>
	helps to open any program, ranging from system programs to self made programs.
	
	pass open update <program name>
		updates the directory of given program

pass try
	opens a notepad window where random things can be written.

pass search <some question>
	searches for the given topic on duckduckgo

	pass seacrh ~g <question>
		searches for the question on google

	pass search ~secure <webpage url>
		gets the source code of the required, then turns off wifi and then displays the webpage on default browser

	pass search ~youtube <video name>
		or
	pass search ~yt <video name>
		opens youtube and searches for the given video in youtube, is useful when you are not trying to lose focus; opens in default browser


pass report
	=> opens report in interactive mode
	
	pass report exit 
		=> exits (very useful for nothing)

	pass report delete <report name>
		=> deletes report and record associated with given report name

	pass report show
		=> shows all existing reports

	pass report create <report name>
		=> a prompt to enter report record is given. hence a report is created.

	pass report update <report name>
		=> updates report record for the given report name. a prompt is given to enter report record.

	pass report start <report name>
		=> starts the timer for the given report and opens the necessary files for starting the work on the report.

	pass report ~start <report name>
		=> starts the timer for the given report without opening the necessary files for starting the work.

pass mcmd <new command name> <args>
	=> an existing command of command prompt can be given a new name with this pass command, it is called a command macro

pass cmd <command>
	=> executes the given command with command prompt

pass show
	shows all existing self-made programs that can be opened using "pass open" command

pass exit
	=> exits pass, it is useful when in interactive mode.

pass sleep
	=> shuts down the computer.
----------------------------------------------------------------
extra features - 
+	you can type a random sentence and end it with a '?' to make it a yes or no question that pass will give a randomised response to
	if you end the sentence with a '!', there may be a surprise.

+	you can add a 'bye' to your random sentence and pass will exit

