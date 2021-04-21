/*
AddTask macro for simple dimuon analysis task.
*/

//-------------------------------------------------------------------------------------------------//
//main function, to be called after compiling the corresponding task.
TaskDimuonPbPb* AddTaskSimpleDimuon()
{
  // Get the pointer to the existing analysis manager via the static access method.
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if(!mgr) {
    Error("AddTaskSimpleDimuon","AliAnalysisManager not set!");
    return NULL;
  }

  // This task run on AODs
  TString type = mgr->GetInputEventHandler()->GetDataType();
  if (!type.Contains("AOD")) {
    Error("AddTaskSimpleDimuon", "AOD input handler needed!");
    return NULL;
  }

  // Create and configure task
  TaskDimuonPbPb *mainTask = new TaskDimuonPbPb("EventMixing",244900,298000);
  if (!mainTask) {
    Error("AddTaskSimpleDimuon", "TaskDimuonPbPb task cannot be created!");
    return NULL;
  }

  // Add task to analysis manager
  mgr->AddTask(mainTask);

  // Connect input container
  mgr->ConnectInput(mainTask, 0, mgr->GetCommonInputContainer());

  // Define output file directory
  TString outputfile = AliAnalysisManager::GetCommonFileName();
  if ( outputfile.IsNull() ) {
    Error("AddTaskMeanTracklets", "Common output file is not defined!");
    return NULL;
  }

  AliAnalysisDataContainer *outputListEvent = mgr->CreateContainer("ListEvent", TObjArray::Class(),    AliAnalysisManager::kOutputContainer,outputfile.Data());
  mgr->ConnectOutput(mainTask, 1, outputListEvent);


  return mainTask;
}
//-------------------------------------------------------------------------------------------------//
