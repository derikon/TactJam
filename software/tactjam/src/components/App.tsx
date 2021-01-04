import React from 'react';
import { makeStyles, Theme } from '@material-ui/core/styles';
import AppBar from '@material-ui/core/AppBar';
import Tabs from '@material-ui/core/Tabs';
import Grid from '@material-ui/core/Grid';
import Tab from '@material-ui/core/Tab';
import Typography from '@material-ui/core/Typography';
import MainLayout from './mainLayout/mainLayout'
import ImportLayout from './importLayout/importLayout'
import SaveLayout from './saveLayout/saveLayout';
import CustomTab from './Navbar/CustomTab';

export enum Layouts {
  MainLayout,
  SaveLayout,
  ImportLayout
}

const useStyles = makeStyles((theme: Theme) => ({
  root: {
    flexGrow: 1,
  },
  tabs: {
    borderStyle: "solid",
    borderBlockColor: 'black',
    borderRightStyle: "none",
    backgroundColor: "#3f51b5",
    minHeight: 40,
    textAlign: 'center',
  },
  lastTab: {
    borderStyle: "solid",
    borderBlockColor: 'black',
    backgroundColor: "#3f51b5",
    minHeight: 40,
    textAlign: 'center',
  }
}));


export default function NavTabs() {
  const classes = useStyles();
  const [activeSlot, setActiveSlot] = React.useState(1);
  const [currentLayout, setCurrentLayout] = React.useState(Layouts.MainLayout);

  const handleChange = (slotNumber: number, layout:Layouts) => {
    console.log(layout);
    setActiveSlot(slotNumber);
    setCurrentLayout(layout)
  };

  return (
    <Grid container spacing={0} className={classes.root}>
      <Grid item xs={4} className={classes.tabs}>
        <CustomTab
          onClickTab={(slotNumber: number, layout:Layouts) => handleChange(slotNumber, layout)}
          slotNumber={1}
        />
      </Grid>
      <Grid item xs={4} className={classes.tabs}>
        <CustomTab
          onClickTab={(slotNumber: number, layout:Layouts) => handleChange(slotNumber, layout)}
          slotNumber={2}
        />
      </Grid>
      <Grid item xs={4} className={classes.lastTab}>
        <CustomTab
          onClickTab={(slotNumber: number, layout:Layouts) => handleChange(slotNumber, layout)}
          slotNumber={3}
        />
      </Grid>
      <Grid item xs={12}>
      {currentLayout === Layouts.MainLayout && <MainLayout/>}
      {currentLayout === Layouts.ImportLayout && <ImportLayout slotNumber={activeSlot}/>}
      {currentLayout === Layouts.SaveLayout && <SaveLayout/>}
      </Grid>
    </Grid>
  );
}